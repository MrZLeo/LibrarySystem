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
const char *userAndPasswordFile = "../user_password.txt";

typedef struct user {
    Authority authority;
    Book *borrowedBook;
    int borrowedBookNum;
    char *userName;

    void (*initUser)(struct user *this);

    void (*login)(struct user *this, const char *authority, const char *password,
                  char *userName);

    void (*changePassword)(struct user *this);

    void (*storeNewPassword)(struct user *this, char *newPassword);

    void (*showBorrowedBooks)(struct user *this);

    void (*returnBook)(struct user *this, char *bookName);

} *User;

bool checkPassword(const char *userName, const char *password) {
    FILE *user_password = fopen(userAndPasswordFile, "r");

    while (!feof(user_password)) {
        char user[maxUserName];
        char passwordInFIle[maxPasswordLength];
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
                printf("密码错误\n");
            else {
                printf("输入管理员密码错误超过三次，系统自动退出。\n");
                system("pause");
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
                printf("密码错误\n");
        }
    } else if (strcmp(authority, "viewer") == 0) {
        this->authority = viewer;
    }

}

void getUserAndPassword(char *userName, char *password) {
    if (strcmp(userName, "root") != 0) {
        assert(strcmp(userName, "student"));

        printf("请输入用户名：\n");
        scanf("%s", userName);
    }
    printf("请输入密码：\n");
    scanf("%s", password);
}

void initUser(User this) {
    char userName[maxUserName] = {0};
    char authority[8] = {0};
    char password[maxPasswordLength] = {0};
    printf("用户等级：\n");
    printf("1. 管理员（root），可以管理图书馆的书籍。\n");
    printf("2. 一般读者（viewer），只能查看图书馆的书籍。\n");
    printf("3. 学生（student），拥有查看、借阅的权限。\n");
    printf("请输入用户等级的英文，e.g. root\n");
    scanf("%s", authority);
    if (strcmp(authority, "viewer") == 0) {
        this->login(this, authority, NULL, NULL);
    } else if (strcmp(authority, "root") == 0) {
        getUserAndPassword("root", password);
        this->login(this, authority, password, NULL);

        while (this->authority == unknown) {

            printf("是否重新输入？（Y/N）\n");
            fflush(stdin);
            char ch;
            scanf("%c", &ch);
            if (ch == 'Y') {
                getUserAndPassword("root", password);
                this->login(this, authority, password, userName);
            } else
                exit(-1);
        }

    } else if (strcmp(authority, "student") == 0) {
        getUserAndPassword(userName, password);
        this->login(this, authority, password, userName);

        while (this->authority == unknown) {

            printf("是否重新输入？（Y/N）\n");
            fflush(stdin);
            char ch;
            scanf("%c", &ch);
            if (ch == 'Y') {
                getUserAndPassword(userName, password);
                this->login(this, authority, password, userName);
            } else {
                exit(-1);
            }
        }

    } else {
        printf("输入错误，是否重新输入？（Y/N）\n");\
        char ch;
        scanf("%c", &ch);
        while (ch == 'Y')
            initUser(this);
        return;
    }

}

void storeNewPassword(User this, char *newPassword) {
    // 这里应该是修改文件原有的密码
    // 但要小心不要抹去其他用户的账号和密码
    FILE *passwordFile = fopen(userAndPasswordFile, "r");
    FILE *newPasswordFile = fopen("../newPasswordFile.txt", "w");
    while (!feof(passwordFile)) {
        char userName[maxUserName];
        char userPassword[maxPasswordLength];
        fscanf(passwordFile, "%s %s", userName, userPassword);
        fprintf(newPasswordFile, "%s\t", userName);
        if (strcmp(this->userName, userName) == 0) {
            fprintf(newPasswordFile, "%s\n", newPassword);
        } else {
            fprintf(newPasswordFile, "%s\n", userPassword);
        }
    }
    fclose(passwordFile);
    fclose(newPasswordFile);
    rename("../newPasswordFile.txt", "user_password.txt");
}

void changePassword(User this) {
    printf("请输入原密码：\n");
    char password[maxPasswordLength];
    scanf("%s", password);
    if (checkPassword(this->userName, password) == true) {
        printf("请输入新密码：\n");
        scanf("%s", password);
        char newPassword[maxPasswordLength];
        printf("请再输入一次新密码：\n");
        scanf("%s", newPassword);
        if (strcmp(password, newPassword) == 0) {
            // 修改密码
            this->storeNewPassword(this, newPassword);
            return;
        }
    } else {
        printf("密码错误");
    }
}

void showBorrowedBooks(User this) {
    Book *prevBook = this->borrowedBook;
    int num = 0;
    while (prevBook->right != NULL) {
        Book *curBook = prevBook->right;
        printf("book %d : 《%s》, bookID: %d\n", num++, curBook->name, curBook->book_ID);
        prevBook = prevBook->right;
    }
}

void returnBook(User this, char *bookName) {
    Book *prevBook = this->borrowedBook;
    while (prevBook->right != NULL) {
        if (strcmp(prevBook->right->name, bookName) == 0) {
            Book *delBook = prevBook->right;
            prevBook->right = delBook->right;
            free(delBook);
            this->borrowedBookNum--;
            return;
        }
        prevBook = prevBook->right;
    }

    printf("没有借阅这本书\n");
}

User new_user() {
    // 申请内存空间
    User user = malloc(sizeof(struct user));

    // 数据初始化
    user->authority = unknown;
    user->borrowedBook = (Book *) calloc(1, sizeof(struct book));
    user->borrowedBookNum = 0;
    user->userName = calloc(maxUserName, sizeof(char));

    // 函数初始化
    user->login = login;
    user->initUser = initUser;
    user->changePassword = changePassword;
    user->storeNewPassword = storeNewPassword;
    user->showBorrowedBooks = showBorrowedBooks;
    user->returnBook = returnBook;

    return user;
}

#endif //LIBRARY_SYSTEM_USER_H
