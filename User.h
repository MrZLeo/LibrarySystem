//
// Created by MrZ on 2020-11-13.
//

#ifndef LIBRARY_SYSTEM_USER_H
#define LIBRARY_SYSTEM_USER_H

#include <string.h>
#include "Basic.h"


typedef enum right {
    root = 0,
    student = 1,
    viewer = 2,
} Right;

char *root_password = "management";

typedef struct User {
    Right right;

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

Right login(const char *userName, const char *password) {
    if (strcmp(userName, "root") == 0) {
        if (strcmp(password, root_password) == 0) {
            return root;
        }
    } else if (strcmp(userName, "student") == 0) {
        if (checkPassword(userName, password) == true) {
            return student;
        }
    }

    exit(-1);
}

#endif //LIBRARY_SYSTEM_USER_H
