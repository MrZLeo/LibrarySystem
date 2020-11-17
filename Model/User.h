//
// Created by MrZ on 2020-11-13.
//

#ifndef LIBRARY_SYSTEM_USER_H
#define LIBRARY_SYSTEM_USER_H

#include <string.h>
#include "../Basic.h"
#include "Book.h"

typedef enum right {
    root = 0,
    student = 1,
    viewer = 2,
    unknown = 3,
} Right;

char *root_password = "yes£¡";

typedef struct user {
    Right right;

    Book borrowedBook[numOfBookInOneTime];

    Right (*login)(char *password);

} User;

bool checkPassword(const char *userName, const char *password) {
    FILE *user_password = fopen("user_password", "r");
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

Right login(const char *authority, const char *password, char *userName) {
    if (strcmp(authority, "root") == 0) {
        if (strcmp(password, root_password) == 0) {
            return root;
        } else {
            printf("ÃÜÂë´íÎó\n");
        }
    } else if (strcmp(authority, "student") == 0) {
        if (checkPassword(userName, password) == true) {
            return student;
        } else {
            printf("ÃÜÂë´íÎó\n");
        }
    } else if (strcmp(authority, "viewer") == 0) {
        return viewer;
    }

    return unknown;
}

User *initUser() {
    User *user = calloc(1, sizeof(struct user));
    char userName[maxUserName];
    char authority[8];
    char password[maxPasswordLength];
    printf("ÇëÊäÈëÓÃ»§µÈ¼¶£º\n");
    scanf("%s", authority);
    if (strcmp(authority, "viewer") == 0) {
        user->right = login(authority, NULL, NULL);
    } else if (strcmp(authority, "root") == 0) {
        printf("ÇëÊäÈëÃÜÂë£º\n");
        scanf("%s", password);
        user->right = login(authority, password, NULL);
    } else if (strcmp(authority, "student") == 0) {
        printf("ÇëÊäÈëÓÃ»§Ãû£º\n");
        scanf("%s", userName);
        printf("ÇëÊäÈëÃÜÂë£º\n");
        scanf("%s", password);
        user->right = login(authority, password, password);
    }

//    user->right = login()
}

#endif //LIBRARY_SYSTEM_USER_H
