//
// Created by MrZ on 2020-11-03.
//

#ifndef LIBRARY_SYSTEM_VIEW_H
#define LIBRARY_SYSTEM_VIEW_H

#include "../Basic.h"
#include "../Model/Bookshelf.h"
#include "../Model/User.h"

const int LIST_LENGTH_OF_MAIN_MENU = 2;
const int LIST_LENGTH_OF_STUDENT_MENU = 4;
const int LIST_LENGTH_OF_ROOT_MENU = 4;
const int LIST_LENGTH_OF_VIEWER_MENU = 2;
const int LENGTH_OF_ONE_SENTENCE = 14;

typedef struct menu {
    int lengthOfMenu;
    const char *menu[LENGTH_OF_ONE_SENTENCE];

    void (*showMenuDetail)(struct menu this);
} Menu;

void showMenuDetail(Menu this) {
    for (int i = 0; i < this.lengthOfMenu; ++i) {
        printf("%s\n", this.menu[i]);
    }
}

const static Menu MAIN_MENU = {
        LIST_LENGTH_OF_MAIN_MENU,
        "0.退出",
        "1.账号登录",
        .showMenuDetail = showMenuDetail,
};

const static Menu STUDENT_MENU = {
        LIST_LENGTH_OF_STUDENT_MENU,
        "1.查看图书",
        "2.借阅图书",
        "3.归还图书",
        "4.退出登录",
        .showMenuDetail = showMenuDetail,
};

const static Menu ROOT_MENU = {
        LIST_LENGTH_OF_ROOT_MENU,
        "1.查看图书",
        "2.上架新书",
        "3.丢弃旧书",
        "4.退出登录",
        .showMenuDetail = showMenuDetail,
};

const static Menu VIEWER_MENU = {
        LIST_LENGTH_OF_VIEWER_MENU,
        "1.查看图书",
        "2.退出登录",
        .showMenuDetail = showMenuDetail,
};


typedef struct view {

    void (*showMenu)();

    void (*showBooks)(Bookshelf bookshelf);
} *View;


void showMenu(View this, Authority authority) {
    fflush(stdout);
    printf("以下为您可选择的操作：\n");
    switch (authority) {
        case root:
            ROOT_MENU.showMenuDetail(ROOT_MENU);
            break;
        case student:
            STUDENT_MENU.showMenuDetail(STUDENT_MENU);
            break;
        default:
            VIEWER_MENU.showMenuDetail(VIEWER_MENU);
            break;
    }
}

void showBooks(Bookshelf bookshelf) {
    bookshelf->showBook(bookshelf);
}

View new_view() {
    // 初始化内存
    View view = malloc(sizeof(struct view));

    // 初始化函数
    view->showBooks = showBooks;
    view->showMenu = showMenu;

    return view;
}

#endif //LIBRARY_SYSTEM_VIEW_H
