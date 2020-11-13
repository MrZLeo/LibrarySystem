//
// Created by MrZ on 2020-11-03.
//

#ifndef LIBRARY_SYSTEM_VIEW_H
#define LIBRARY_SYSTEM_VIEW_H

#include "Basic.h"

const int listLength = 2;
const char menu[][14] = {"1.账号登录",
                         "2.借阅图书",};


typedef struct view {

    void (*viewMenu)(const char **, int);
} View;

void viewMenu(const char **menuOf, const int Length) {
    printf("欢迎来到图书馆\n");
    printf("请先完成登录：\n");
    printf("以下为您可选择的操作：\n");
    for (int i = 0; i < Length; ++i) {
        printf("%s\n", menuOf[i]);
    }
}

#endif //LIBRARY_SYSTEM_VIEW_H
