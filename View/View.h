//
// Created by MrZ on 2020-11-03.
//

#ifndef LIBRARY_SYSTEM_VIEW_H
#define LIBRARY_SYSTEM_VIEW_H

#include "../Model/Bookshelf.h"
#include "../Model/User.h"

const int LIST_LENGTH_OF_MAIN_MENU = 3;
const int LIST_LENGTH_OF_STUDENT_MENU = 7;
const int LIST_LENGTH_OF_ROOT_MENU = 5;
const int LIST_LENGTH_OF_VIEWER_MENU = 3;

#define LENGTH_OF_ONE_SENTENCE  14

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

const Menu MAIN_MENU = {
        LIST_LENGTH_OF_MAIN_MENU,
        "0.退出",
        "1.账号登录",
        "2.账号注册",
        .showMenuDetail = showMenuDetail,
};

const Menu STUDENT_MENU = {
        LIST_LENGTH_OF_STUDENT_MENU,
        "1.查看图书",
        "2.借阅图书",
        "3.归还图书",
        "4.已借图书",
        "5.返回上级",
        "6.修改密码",
        "7.退出系统",
        .showMenuDetail = showMenuDetail,
};

const Menu ROOT_MENU = {
        LIST_LENGTH_OF_ROOT_MENU,
        "1.查看图书",
        "2.上架新书",
        "3.丢弃旧书",
        "4.返回上级",
        "5.退出系统",
        .showMenuDetail = showMenuDetail,
};

const Menu VIEWER_MENU = {
        LIST_LENGTH_OF_VIEWER_MENU,
        "1.查看图书",
        "2.返回上级",
        "3.退出系统",
        .showMenuDetail = showMenuDetail,
};

typedef enum layer {
    first = 1,
    second = 2,
} Layer;

typedef struct view {
    Menu mainMenu;
    Menu studentMenu;
    Menu rootMenu;
    Menu viewerMenu;

    Layer layer;

    void (*show)(struct view *this, User user);

    void (*showMenu)(struct view *this, Authority authority);

    void (*showUser)(User user);

    void (*showBooks)(Bookshelf bookshelf);
} *View;

void showMenu(View this, Authority authority) {
    printf("以下为您可选择的操作：\n");
    switch (authority) {
        case root:
            this->rootMenu.showMenuDetail(this->rootMenu);
            break;
        case student:
            this->studentMenu.showMenuDetail(this->studentMenu);
            break;
        case viewer:
            this->viewerMenu.showMenuDetail(this->viewerMenu);
        default:
            this->mainMenu.showMenuDetail(this->mainMenu);
            break;
    }
}

void showBooks(Bookshelf bookshelf) {
    bookshelf->showBook(bookshelf);
}

void showUser(User user) {
    switch (user->authority) {
        case root:
            printf("你好，图书馆管理员。\n");
            break;
        case student:
            printf("你好，%s。\n", user->userName);
            break;
        case viewer:
            printf("你好。\n");
        default:
            break;
    }
}

void show(View this, User user) {
    system("cls");
    if (this->layer == first) {
        printf("欢迎来到图书馆。\n");
        printf("请先登录您的帐号：\n");
        this->showMenu(this, unknown);
    } else {
        assert(this->layer == second);
        // 第二级菜单时需要考虑不同的身份。
        this->showUser(user);
        this->showMenu(this, user->authority);
    }

}


View new_view() {
    // 初始化内存
    View view = malloc(sizeof(struct view));

    // 初始化成员变量
    view->mainMenu = MAIN_MENU;
    view->studentMenu = STUDENT_MENU;
    view->rootMenu = ROOT_MENU;
    view->viewerMenu = VIEWER_MENU;

    view->layer = first;

    // 初始化函数
    view->show = show;
    view->showUser = showUser;
    view->showBooks = showBooks;
    view->showMenu = showMenu;

    return view;
}

#endif //LIBRARY_SYSTEM_VIEW_H
