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

    void (*user_changePassword)(struct controller *this);

    void (*userBorrowBook)(struct controller *this, char *bookName);

    void (*userReturnBook)(struct controller *this, char *bookName);

    void (*showUserBorrowedBook)(struct controller *this);

    void (*init_bookshelf)(struct controller *this, FILE *books);

    void (*store_bookshelf)(struct controller *this, FILE *books);

    void (*readBooks)(struct controller *this);

    bool (*addBookToBookshelf)(struct controller *this, char *bookName);

    int (*findBookInBookshelf)(struct controller *this, char *bookName);

    bool (*removeBookInBookshelf)(struct controller *this, char *bookName);

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

void user_changePassword(Controller this) {
    this->user->changePassword(this->user);
}

void userBorrowBook(Controller this, char *bookName) {

    if (this->user->borrowedBookNum == numOfBookInOneTime) {
        printf("以达到同时借阅书籍上限\n");
        system("pause");
        return;
    }

    int bookID = this->findBookInBookshelf(this, bookName);
    if (bookID == -1) {
        printf("没有找到这本书\n");
        system("pause");
        return;
    }

    Book *book = new_Book(bookID, bookName);
    Book *prevBook = this->user->borrowedBook;
    while (prevBook->right != NULL)
        prevBook = prevBook->right;
    prevBook->right = book;
    this->user->borrowedBookNum++;
    printf("借阅成功\n");
}

void userReturnBook(Controller this, char *bookName) {
    return this->user->returnBook(this->user, bookName);
}

void showUserBorrowedBook(Controller this) {
    this->user->showBorrowedBooks(this->user);
}

void init_bookshelf(Controller this, FILE *books) {
    this->bookshelf->initBookshelf(this->bookshelf, books);
}

void store_bookShelf(Controller this, FILE *books) {
    this->bookshelf->storeBookshelf(this->bookshelf, books);
}

void readBooks(Controller this) {
    this->view->showBooks(this->bookshelf);
}

bool addBookToBookshelf(Controller this, char *bookName) {
    return this->bookshelf->addBook(this->bookshelf, bookName);
}

int findBookInBookshelf(Controller this, char *bookName) {
    return this->bookshelf->findBook(this->bookshelf, bookName);
}

bool removeBookInBookshelf(Controller this, char *bookName) {
    return this->bookshelf->removeBook(this->bookshelf, bookName);
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
            this->userBorrowBook(this, bookName);
            break;
        }
        case 3: {
            printf("请输入书名: ");
            char bookName[maxBookName];
            scanf("%s", bookName);
            this->userReturnBook(this, bookName);
            break;
        }
        case 4: {
            printf("已借图书：\n");
            this->showUserBorrowedBook(this);
            system("pause");
            break;
        }
        case 5:
            this->view->layer--;
            system("cls");
            break;
        case 6:
            this->user_changePassword(this);
            system("pause");
            break;
        case 7:
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
    // TODO 需要增加用户的可操作性，例如修改密码。
    if (this->view->layer == first) {
        switch (info) {
            case 1:
                this->user_login(this);
                this->view->layer++;
                system("cls");
                return false;
            case 2:
                // TODO 加一个注册功能
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

    // 登陆时首先读取系统保存的书籍信息
    this->init_bookshelf(this, fopen("../books.txt", "r"));

    // 主程序循环
    while (!isToStop) {
        this->view->show(this->view, this->user);
        int info = 0;
        scanf("%d", &info);
        isToStop = this->runInDifferentLayer(this, info);
    }

    // 退出整个程序的时候需要把书籍信息写入文件
    this->store_bookshelf(this, fopen("../books.txt", "r"));

    printf("--------END--------\n");
}

Controller new_controller() {
    // 初始化内存
    Controller controller = malloc(sizeof(struct controller));

    // 初始化函数
    controller->setController = setController;
    controller->user_login = user_login;
    controller->user_changePassword = user_changePassword;
    controller->userBorrowBook = userBorrowBook;
    controller->userReturnBook = userReturnBook;
    controller->showUserBorrowedBook = showUserBorrowedBook;
    controller->init_bookshelf = init_bookshelf;
    controller->store_bookshelf = store_bookShelf;
    controller->readBooks = readBooks;
    controller->addBookToBookshelf = addBookToBookshelf;
    controller->findBookInBookshelf = findBookInBookshelf;
    controller->removeBookInBookshelf = removeBookInBookshelf;
    controller->runInDifferentLayer = runInDifferentLayer;
    controller->runRoot = runRoot;
    controller->runStudent = runStudent;
    controller->runViewer = runViewer;
    controller->run = run;

    return controller;
}


#endif //LIBRARY_SYSTEM_CONTROLLER_H