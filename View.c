//
// Created by MrZ on 2020-11-03.
//

#include "View.h"

void viewMenu(const char **menuOf, const int Length) {
    printf("��ӭ����ͼ���\n");
    printf("������ɵ�¼��\n");
    // TODO:��½����
    printf("����Ϊ����ѡ��Ĳ�����\n");
    for (int i = 0; i < Length; ++i) {
        printf("%s\n", menuOf[i]);
    }
}
