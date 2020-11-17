//
// Created by MrZ on 2020-11-13.
//

#ifndef LIBRARY_SYSTEM_USER_H
#define LIBRARY_SYSTEM_USER_H

#include <string.h>
#include "../Basic.h"
#include "Book.h"

typedef enum authority {
    root = 0,
    student = 1,
    viewer = 2,
    unknown = 3,
} Authority;

char *root_password = "yes��";
static int wrongTimeOfRoot = 0;
static int wrongTimeOfStudent = 0;
const int MAX_TIMES_TO_TRY = 3;

typedef struct user {
    Authority authority;
    Book *borrowedBook;


    void (*initUser)(struct user *this);

    Authority (*login)(struct user *this, const char *authority, const char *password,
                       char *userName);

} *User;

bool checkPassword(const char *userName, const char *password) {
    FILE *user_password = fopen("user_password.txt", "r");

    while (!feof(user_password)) {
        char *user = NULL;
        char *passwordInFIle = NULL;
        fscanf(user_password, "%s", user);
        fscanf(user_password, "%s", passwordInFIle);
        fgetchar();
        if (strcmp(user, userName) == 0) {
            if (strcmp(password, passwordInFIle) == 0) {
                return true;
            }
        }
    }
    fclose(user_password);

    return false;
}

void login(User this, const char *authority, const char *password, char *userName) {
    if (strcmp(authority, "root") == 0) {
        if (strcmp(password, root_password) == 0) {
            this->authority = root;
        } else {
            wrongTimeOfRoot++;
            if (wrongTimeOfRoot < MAX_TIMES_TO_TRY)
                printf("�������\n");
            else {
                printf("�������Ա������󳬹����Σ�ϵͳ�Զ��˳���\n");
                exit(1);
            }
        }
    } else if (strcmp(authority, "student") == 0) {
        if (checkPassword(userName, password) == true) {
            this->authority = student;
        } else {
            wrongTimeOfStudent++;
            if (wrongTimeOfStudent < MAX_TIMES_TO_TRY)
                printf("�������\n");
        }
    } else if (strcmp(authority, "viewer") == 0) {
        this->authority = viewer;
    }

}

void initUser(User this) {
    char userName[maxUserName];
    char authority[8];
    char password[maxPasswordLength];
    printf("�û��ȼ���\n");
    printf("1. ����Ա��root�������Թ���ͼ��ݵ��鼮��\n");
    printf("2. һ����ߣ�viewer����ֻ�ܲ鿴ͼ��ݵ��鼮��\n");
    printf("3. ѧ����student����ӵ�в鿴�����ĵ�Ȩ�ޡ�\n");
    printf("�������û��ȼ���Ӣ�ģ�e.g. root\n");
    scanf("%s", authority);
    if (strcmp(authority, "viewer") == 0) {
        login(this, authority, NULL, NULL);
    } else if (strcmp(authority, "root") == 0) {
        printf("���������룺\n");
        scanf("%s", password);
        login(this, authority, password, NULL);
    } else if (strcmp(authority, "student") == 0) {
        printf("�������û�����\n");
        scanf("%s", userName);
        printf("���������룺\n");
        scanf("%s", password);
        login(this, authority, password, userName);

        if (this->authority == unknown) {

            printf("�Ƿ��������룿��Y/N��\n");
            char ch;
            scanf("%c", &ch);
            if (ch == 'Y') {
                printf("�������û�����\n");
                scanf("%s", userName);
                printf("���������룺\n");
                scanf("%s", password);
                login(this, authority, password, userName);
            }
        }

    } else {
        printf("��������Ƿ��������룿��Y/N��\n");\
        char ch;
        scanf("%c", &ch);
        if (ch == 'Y')
            initUser(this);
        else
            return;
    }

}

User new_user() {
    User user = malloc(sizeof(struct user));
    user->authority = unknown;
    user->borrowedBook = calloc(numOfBookInOneTime, sizeof(struct book));
    user->login = login;
    user->initUser = initUser;

    return user;
}

#endif //LIBRARY_SYSTEM_USER_H
