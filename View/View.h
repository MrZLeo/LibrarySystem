//
// Created by MrZ on 2020-11-03.
//

#ifndef LIBRARY_SYSTEM_VIEW_H
#define LIBRARY_SYSTEM_VIEW_H

#include "../Basic.h"
#include "../Model/Bookshelf.h"

const int listLength = 7;
const char menu[][14] = {"0.�˳�",
                         "1.�˺ŵ�¼",
                         "2.�鿴ͼ��",
                         "3.����ͼ��",
                         "4.�黹ͼ��",
                         "5.�ϼ�����",
                         "6.��������",
};


typedef struct view {

    void (*showMenu)();

    void (*showBooks)(Bookshelf bookshelf);
} *View;

void showMenu(View this) {
    printf("����Ϊ����ѡ��Ĳ�����\n");
    for (int i = 0; i < listLength; ++i) {
        printf("%s\n", menu[i]);
    }
}

void showBooks(Bookshelf bookshelf) {
    bookshelf->showBook(bookshelf);
}

View new_view() {
    // ��ʼ���ڴ�
    View view = malloc(sizeof(struct view));

    // ��ʼ������
    view->showBooks = showBooks;
    view->showMenu = showMenu;

    return view;
}

#endif //LIBRARY_SYSTEM_VIEW_H
