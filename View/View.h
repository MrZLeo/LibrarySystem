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
        "0.�˳�",
        "1.�˺ŵ�¼",
        "2.�˺�ע��",
        .showMenuDetail = showMenuDetail,
};

const Menu STUDENT_MENU = {
        LIST_LENGTH_OF_STUDENT_MENU,
        "1.�鿴ͼ��",
        "2.����ͼ��",
        "3.�黹ͼ��",
        "4.�ѽ�ͼ��",
        "5.�����ϼ�",
        "6.�޸�����",
        "7.�˳�ϵͳ",
        .showMenuDetail = showMenuDetail,
};

const Menu ROOT_MENU = {
        LIST_LENGTH_OF_ROOT_MENU,
        "1.�鿴ͼ��",
        "2.�ϼ�����",
        "3.��������",
        "4.�����ϼ�",
        "5.�˳�ϵͳ",
        .showMenuDetail = showMenuDetail,
};

const Menu VIEWER_MENU = {
        LIST_LENGTH_OF_VIEWER_MENU,
        "1.�鿴ͼ��",
        "2.�����ϼ�",
        "3.�˳�ϵͳ",
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
    printf("����Ϊ����ѡ��Ĳ�����\n");
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
            printf("��ã�ͼ��ݹ���Ա��\n");
            break;
        case student:
            printf("��ã�%s��\n", user->userName);
            break;
        case viewer:
            printf("��á�\n");
        default:
            break;
    }
}

void show(View this, User user) {
    system("cls");
    if (this->layer == first) {
        printf("��ӭ����ͼ��ݡ�\n");
        printf("���ȵ�¼�����ʺţ�\n");
        this->showMenu(this, unknown);
    } else {
        assert(this->layer == second);
        // �ڶ����˵�ʱ��Ҫ���ǲ�ͬ����ݡ�
        this->showUser(user);
        this->showMenu(this, user->authority);
    }

}


View new_view() {
    // ��ʼ���ڴ�
    View view = malloc(sizeof(struct view));

    // ��ʼ����Ա����
    view->mainMenu = MAIN_MENU;
    view->studentMenu = STUDENT_MENU;
    view->rootMenu = ROOT_MENU;
    view->viewerMenu = VIEWER_MENU;

    view->layer = first;

    // ��ʼ������
    view->show = show;
    view->showUser = showUser;
    view->showBooks = showBooks;
    view->showMenu = showMenu;

    return view;
}

#endif //LIBRARY_SYSTEM_VIEW_H
