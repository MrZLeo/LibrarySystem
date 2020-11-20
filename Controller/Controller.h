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

    void (*addBookToBookshelf)(struct controller *this, char *bookName);

    void (*findBookInBookshelf)(struct controller *this, char *bookName);

    void (*removeBookInBookshelf)(struct controller *this, char *bookName);

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
}

void returnBook(Controller this, char *bookName) {

    for (int i = 0; i < this->user->borrowedBookNum; ++i) {
        if (strcmp(this->user->borrowedBook[i]->name, bookName) == 0) {
            for (int j = i; j < this->user->borrowedBookNum; ++j) {
                this->user->borrowedBook[j] = this->user->borrowedBook[j + 1];
            }
            this->user->borrowedBookNum--;
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

void addBookToBookshelf(Controller this, char *bookName) {
    this->bookshelf->addBook(this->bookshelf, bookName);
}

void findBookInBookshelf(Controller this, char *bookName) {
    this->bookshelf->findBook(this->bookshelf, bookName);
}

void removeBookInBookshelf(Controller this, char *bookName) {
    this->bookshelf->removeBook(this->bookshelf, bookName);
}

//void throwAllBooks(Controller this) {
//    this->bookshelf->free_Bookshelf(this->bookshelf);
//}

void run(Controller this) {
    bool isToStop = false;
    printf("欢迎来到图书馆\n");

    // TODO 进入图书馆后的第一步应该要将文件中的书籍读入系统进行动态处理。
    // ...

    printf("请先登录账号：\n");
    char bookName[maxBookName] = {0};
    while (!isToStop) {
        this->view->showMenu();
        int info;
        scanf("%d", &info);

        fflush(stdin);
        switch (info) {
            case 0:
                // TODO 关闭前需要将当前书籍存储到文件内。
                // ...
                printf("---------END---------\n");
                isToStop = true;
                break;

            case 1:
                this->user_login(this);
                break;

            case 2:
                assert(this->user->authority != unknown);
                this->readBooks(this);
                break;

            case 3:
                assert(this->user->authority == student);
                printf("当前图书馆拥有的图书：\n");
                this->readBooks(this);
                printf("请输入你想借阅的图书：\n");
                scanf("%s", bookName);
                this->borrowBook(this, bookName);
                break;

            case 4:
                assert(this->user->authority == student);
                printf("你已借阅的图书：\n");
                this->showUserBorrowedBook(this);
                break;

            case 5:
                assert(this->user->authority == root);
                printf("请输入你想要上架的新书名称：\n");
                scanf("%s", bookName);
                this->addBookToBookshelf(this, bookName);
                break;

            case 6:
                assert(this->user->authority == root);
                printf("请输入你想要丢弃的旧书名称：\n");
                scanf("%s", bookName);
                this->removeBookInBookshelf(this, bookName);
                break;

            default:
                printf("输入错误。\n");
                break;
        }
    }


    printf("no bug!\n");
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
    controller->run = run;

    return controller;
}


#endif //LIBRARY_SYSTEM_CONTROLLER_H