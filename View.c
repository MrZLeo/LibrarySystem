//
// Created by MrZ on 2020-11-03.
//

#include "View.h"

void viewMenu(const char **menuOf, const int Length) {
    printf("欢迎来到图书馆\n");
    printf("请先完成登录：\n");
    // TODO:登陆操作
    printf("以下为您可选择的操作：\n");
    for (int i = 0; i < Length; ++i) {
        printf("%s\n", menuOf[i]);
    }
}
