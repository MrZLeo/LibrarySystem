//
// Created by MrZ on 2020-11-13.
//

#ifndef LIBRARY_SYSTEM_USER_H
#define LIBRARY_SYSTEM_USER_H


#include "../Basic.h"
#include "Book.h"

typedef enum authority {
    root = 0,
    student = 1,
    viewer = 2,
    unknown = 3,
} Authority;

char *root_password = "123456";
static int wrongTimeOfRoot = 0;
static int wrongTimeOfStudent = 0;
const int MAX_TIMES_TO_TRY = 3;

typedef struct user {
    Authority authority;
    Book **borrowedBook;
    int borrowedBookNum;
    char *userName;

    void (*initUser)(struct user *this);

    void (*login)(struct user *this, const char *authority, const char *password,
                  char *userName);

    void (*showBorrowedBooks)(struct user *this);

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
                fclose(user_password);
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
                exit(-1);
            }
        }
    } else if (strcmp(authority, "student") == 0) {
        if (checkPassword(userName, password) == true) {
            this->authority = student;
            this->userName = strcpy(this->userName, userName);
        } else {
            wrongTimeOfStudent++;
            if (wrongTimeOfStudent < MAX_TIMES_TO_TRY)
                printf("�������\n");
        }
    } else if (strcmp(authority, "viewer") == 0) {
        this->authority = viewer;
    }

}

void getUserAndPassword(char *userName, char *password) {
    if (strcmp(userName, "root") != 0) {
        assert(strcmp(userName, "student"));

        printf("�������û�����\n");
        scanf("%s", userName);
    }
    printf("���������룺\n");
    scanf("%s", password);
}

void initUser(User this) {
    char userName[maxUserName] = {0};
    char authority[8] = {0};
    char password[maxPasswordLength] = {0};
    printf("�û��ȼ���\n");
    printf("1. ����Ա��root�������Թ���ͼ��ݵ��鼮��\n");
    printf("2. һ����ߣ�viewer����ֻ�ܲ鿴ͼ��ݵ��鼮��\n");
    printf("3. ѧ����student����ӵ�в鿴�����ĵ�Ȩ�ޡ�\n");
    printf("�������û��ȼ���Ӣ�ģ�e.g. root\n");
    scanf("%s", authority);
    if (strcmp(authority, "viewer") == 0) {
        this->login(this, authority, NULL, NULL);
    } else if (strcmp(authority, "root") == 0) {
        getUserAndPassword("root", password);
        this->login(this, authority, password, NULL);

        while (this->authority == unknown) {

            printf("�Ƿ��������룿��Y/N��\n");
            fflush(stdin);
            char ch;
            scanf("%c", &ch);
            if (ch == 'Y') {
                getUserAndPassword("root", password);
                this->login(this, authority, password, userName);
            }
        }

    } else if (strcmp(authority, "student") == 0) {
        getUserAndPassword(userName, password);
        this->login(this, authority, password, userName);

        while (this->authority == unknown) {

            printf("�Ƿ��������룿��Y/N��\n");
            fflush(stdin);
            char ch;
            scanf("%c", &ch);
            if (ch == 'Y') {
                getUserAndPassword(userName, password);
                this->login(this, authority, password, userName);
            }
        }

    } else {
        printf("��������Ƿ��������룿��Y/N��\n");\
        char ch;
        scanf("%c", &ch);
        while (ch == 'Y')
            initUser(this);
        return;
    }

}

void showBorrowedBooks(User this) {
    for (int i = 0; i < this->borrowedBookNum; ++i) {
        printf("Book%d: %s\n", i, this->borrowedBook[i]->name);
    }
}

User new_user() {
    // �����ڴ�ռ�
    User user = malloc(sizeof(struct user));

    // ���ݳ�ʼ��
    user->authority = unknown;
    user->borrowedBook = calloc(numOfBookInOneTime, sizeof(struct book));
    user->borrowedBookNum = 0;
    user->userName = calloc(maxUserName, sizeof(char));
    
    // ������ʼ��
    user->login = login;
    user->initUser = initUser;
    user->showBorrowedBooks = showBorrowedBooks;

    return user;
}

#endif //LIBRARY_SYSTEM_USER_H
