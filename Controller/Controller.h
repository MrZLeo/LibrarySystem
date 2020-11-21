//
// Created by MrZ on 2020-11-03.
//

#ifndef LIBRARY_SYSTEM_CONTROLLER_H
#define LIBRARY_SYSTEM_CONTROLLER_H

#include "../Basic.h"
#include "../View/View.h"
#include "../Model/Bookshelf.h"
#include "../Model/User.h"

typedef struct controller {

    View view;
    User user;
    Bookshelf bookshelf;

    void (*setController)(struct controller *this, View view, Bookshelf bookshelf, User user);

    void (*user_login)(struct controller *this);

    void (*borrowBook)(struct controller *this, char *bookName);

    void (*returnBook)(struct controller *this, char *bookName);

    void (*showUserBorrowedBook)(struct controller *this);

    void (*bookshelf_setID)(struct controller *this);

    void (*init_bookshelf)(struct controller *this);

    void (*readBooks)(struct controller *this);

    bool (*addBookToBookshelf)(struct controller *this, char *bookName);

    void (*findBookInBookshelf)(struct controller *this, char *bookName);

    bool (*removeBookInBookshelf)(struct controller *this, char *bookName);

    void (*loadBook)(struct controller *this, FILE *books);

    bool (*runRoot)(struct controller *this, int info);

    bool (*runStudent)(struct controller *this, int info);

    bool (*runViewer)(struct controller *this, int info);

    bool (*runInDifferentLayer)(struct controller *this, int info);

    void (*run)(struct controller *this);

} *Controller;

void setController(Controller this, View view, Bookshelf bookshelf, User user) {
    this->view = view;
    this->bookshelf = bookshelf;
    this->user = user;
}


void user_login(Controller this) {
    this->user->initUser(this->user);
}

void borrowBook(Controller this, char *bookName) {

    int bookID = this->bookshelf->findBook(this->bookshelf, bookName);
    if (bookID == -1) {
        printf("没有找到这本书\n");
        return;
    }

    Book *book = new_Book(bookID, bookName);
    this->user->borrowedBook[++this->user->borrowedBookNum] = book;
    printf("借阅成功\n");
}

// FIXME 不知道问题在哪，晚点debug
void returnBook(Controller this, char *bookName) {

    for (int i = 0; i < this->user->borrowedBookNum; ++i) {
        if (strcmp(this->user->borrowedBook[i]->name, bookName) == 0) {
            for (int j = i; j < this->user->borrowedBookNum; ++j) {
                this->user->borrowedBook[j] = this->user->borrowedBook[j + 1];
            }
            this->user->borrowedBookNum--;
            printf("还书成功\n");
            return;
        }
    }

    // 如果没找到
    printf("没有借阅这本书\n");
}

void showUserBorrowedBook(Controller this) {
    this->user->showBorrowedBooks(this->user);
}

void bookshelf_setID(Controller this) {
    this->bookshelf->setID(this->bookshelf);
}

void init_bookshelf(Controller this) {
    this->bookshelf->initBookshelf(this->bookshelf);
}

void readBooks(Controller this) {
    this->view->showBooks(this->bookshelf);
}

bool addBookToBookshelf(Controller this, char *bookName) {
    return this->bookshelf->addBook(this->bookshelf, bookName);
}

void findBookInBookshelf(Controller this, char *bookName) {
    this->bookshelf->findBook(this->bookshelf, bookName);
}

bool removeBookInBookshelf(Controller this, char *bookName) {
    return this->bookshelf->removeBook(this->bookshelf, bookName);
}

void loadBook(Controller this, FILE *books) {
    while (!feof(books)) {
        char bookName[maxBookName];
        fscanf(books, "%s", bookName);
        this->addBookToBookshelf(this, bookName);
    }
    fclose(books);
}

bool runRoot(Controller this, int info) {
    switch (info) {
        case 1:
            printf("馆藏图书：\n");
            this->readBooks(this);
            system("pause");
            break;
        case 2: {
            printf("请输入书名: ");
            char bookName[maxBookName];
            scanf("%s", bookName);
            if (this->addBookToBookshelf(this, bookName)) {
                printf("添加成功\n");
                system("pause");
            }
            break;
        }
        case 3: {
            printf("请输入书名: ");
            char bookName[maxBookName];
            scanf("%s", bookName);
            if (this->removeBookInBookshelf(this, bookName)) {
                printf("删除成功\n");
                system("pause");
            }
            break;
        }
        case 4:
            this->view->layer--;
            system("cls");
            break;
        case 5:
        default:
            return true;
    }

    return false;
}

bool runStudent(Controller this, int info) {
    switch (info) {
        case 1:
            printf("馆藏图书：\n");
            this->readBooks(this);
            system("pause");
            break;
        case 2: {
            printf("请输入书名: ");
            char bookName[maxBookName];
            scanf("%s", bookName);
            this->borrowBook(this, bookName);
            break;
        }
        case 3: {
            printf("请输入书名: ");
            char bookName[maxBookName];
            scanf("%s", bookName);
            this->returnBook(this, bookName);
            break;
        }
        case 4:
            this->view->layer--;
            system("cls");
            break;
        case 5:
        default:
            return true;
    }

    return false;
}

bool runViewer(Controller this, int info) {
    switch (info) {
        case 1:
            printf("馆藏图书：\n");
            this->readBooks(this);
            system("pause");
            break;
        case 2:
            this->view->layer--;
            system("cls");
            break;
        case 3:
        default:
            return true;
    }

    return false;
}

/**
 * 根据不同的layer进行不同的处理
 * @param this
 * @param layer 当前菜单的层数
 * @param info 执行的菜单命令
 * @return 是否退出程序
 */
bool runInDifferentLayer(Controller this, int info) {
    if (this->view->layer == first) {
        switch (info) {
            case 1:
                this->user_login(this);
                this->view->layer++;
                system("cls");
                return false;
            case 0:
            default: // TODO 这里是否需要容错机制？
                return true;
        }
    } else { // layer == second
        assert(this->view->layer == second);

        // 知道 layer==second 还不能解决问题，这里还得分user处理.
        // TODO 是全部写在一起，还是再度抽象？ A：再度抽象
        switch (this->user->authority) {
            case root:
                return this->runRoot(this, info);
            case student:
                return this->runStudent(this, info);
            case viewer:
                return this->runViewer(this, info);
            default:
                return true;
        }
    }

}

/**
 * 系统运行主函数
 */
void run(Controller this) {
    bool isToStop = false;

    // TODO 进入图书馆后的第一步应该要将文件中的书籍读入系统进行动态处理。
    this->loadBook(this, fopen("../books.txt", "r"));

    // 不仅仅是view需要知道layer，controller也需要
    while (!isToStop) {
        this->view->show(this->view, this->user);
        int info = 0;
        scanf("%d", &info);
        isToStop = this->runInDifferentLayer(this, info);
    }

    printf("--------END--------\n");
}

Controller new_controller() {
    // 初始化内存
    Controller controller = malloc(sizeof(struct controller));

    // 初始化函数
    controller->setController = setController;
    controller->user_login = user_login;
    controller->borrowBook = borrowBook;
    controller->returnBook = returnBook;
    controller->showUserBorrowedBook = showUserBorrowedBook;
    controller->init_bookshelf = init_bookshelf;
    controller->readBooks = readBooks;
    controller->addBookToBookshelf = addBookToBookshelf;
    controller->findBookInBookshelf = findBookInBookshelf;
    controller->removeBookInBookshelf = removeBookInBookshelf;
    controller->loadBook = loadBook;
    controller->runInDifferentLayer = runInDifferentLayer;
    controller->runRoot = runRoot;
    controller->runStudent = runStudent;
    controller->runViewer = runViewer;
    controller->run = run;

    return controller;
}


#endif //LIBRARY_SYSTEM_CONTROLLER_H