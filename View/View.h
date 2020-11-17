//
// Created by MrZ on 2020-11-03.
//

#ifndef LIBRARY_SYSTEM_VIEW_H
#define LIBRARY_SYSTEM_VIEW_H

#include "../Basic.h"
#include "../Model/Bookshelf.h"

const int listLength = 7;
const char menu[][14] = {"0.退出",
                         "1.账号登录",
                         "2.查看图书",
                         "3.借阅图书",
                         "4.归还图书",
                         "5.上架新书",
                         "6.丢弃旧书",
};


typedef struct view {

    void (*showMenu)();

    void (*showBooks)(Bookshelf bookshelf);
} *View;

void showMenu(View this) {
    printf("以下为您可选择的操作：\n");
    for (int i = 0; i < listLength; ++i) {
        printf("%s\n", menu[i]);
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
