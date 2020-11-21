//
// Created by MrZ on 2020-11-03.
//

#ifndef LIBRARY_SYSTEM_CONTROLLER_H
#define LIBRARY_SYSTEM_CONTROLLER_H

#include "../Basic.h"
#include "../View/View.h"
#include "../Model/Bookshelf.h"
#include "../Model/User.h"

typedef struct controller {

    View view;
    User user;
    Bookshelf bookshelf;

    void (*setController)(struct controller *this, View view, Bookshelf bookshelf, User user);

    void (*user_login)(struct controller *this);

    void (*borrowBook)(struct controller *this, char *bookName);

    void (*returnBook)(struct controller *this, char *bookName);

    void (*showUserBorrowedBook)(struct controller *this);

    void (*bookshelf_setID)(struct controller *this);

    void (*init_bookshelf)(struct controller *this);

    void (*readBooks)(struct controller *this);

    bool (*addBookToBookshelf)(struct controller *this, char *bookName);

    void (*findBookInBookshelf)(struct controller *this, char *bookName);

    bool (*removeBookInBookshelf)(struct controller *this, char *bookName);

    void (*loadBook)(struct controller *this, FILE *books);

    bool (*runRoot)(struct controller *this, int info);

    bool (*runStudent)(struct controller *this, int info);

    bool (*runViewer)(struct controller *this, int info);

    bool (*runInDifferentLayer)(struct controller *this, int info);

    void (*run)(struct controller *this);

} *Controller;

void setController(Controller this, View view, Bookshelf bookshelf, User user) {
    this->view = view;
    this->bookshelf = bookshelf;
    this->user = user;
}


void user_login(Controller this) {
    this->user->initUser(this->user);
}

void borrowBook(Controller this, char *bookName) {

    int bookID = this->bookshelf->findBook(this->bookshelf, bookName);
    if (bookID == -1) {
        printf("û���ҵ��Ȿ��\n");
        return;
    }

    Book *book = new_Book(bookID, bookName);
    this->user->borrowedBook[++this->user->borrowedBookNum] = book;
    printf("���ĳɹ�\n");
}

// FIXME ��֪���������ģ����debug
void returnBook(Controller this, char *bookName) {

    for (int i = 0; i < this->user->borrowedBookNum; ++i) {
        if (strcmp(this->user->borrowedBook[i]->name, bookName) == 0) {
            for (int j = i; j < this->user->borrowedBookNum; ++j) {
                this->user->borrowedBook[j] = this->user->borrowedBook[j + 1];
            }
            this->user->borrowedBookNum--;
            printf("����ɹ�\n");
            return;
        }
    }

    // ���û�ҵ�
    printf("û�н����Ȿ��\n");
}

void showUserBorrowedBook(Controller this) {
    this->user->showBorrowedBooks(this->user);
}

void bookshelf_setID(Controller this) {
    this->bookshelf->setID(this->bookshelf);
}

void init_bookshelf(Controller this) {
    this->bookshelf->initBookshelf(this->bookshelf);
}

void readBooks(Controller this) {
    this->view->showBooks(this->bookshelf);
}

bool addBookToBookshelf(Controller this, char *bookName) {
    return this->bookshelf->addBook(this->bookshelf, bookName);
}

void findBookInBookshelf(Controller this, char *bookName) {
    this->bookshelf->findBook(this->bookshelf, bookName);
}

bool removeBookInBookshelf(Controller this, char *bookName) {
    return this->bookshelf->removeBook(this->bookshelf, bookName);
}

void loadBook(Controller this, FILE *books) {
    while (!feof(books)) {
        char bookName[maxBookName];
        fscanf(books, "%s", bookName);
        this->addBookToBookshelf(this, bookName);
    }
    fclose(books);
}

bool runRoot(Controller this, int info) {
    switch (info) {
        case 1:
            printf("�ݲ�ͼ�飺\n");
            this->readBooks(this);
            system("pause");
            break;
        case 2: {
            printf("����������: ");
            char bookName[maxBookName];
            scanf("%s", bookName);
            if (this->addBookToBookshelf(this, bookName)) {
                printf("��ӳɹ�\n");
                system("pause");
            }
            break;
        }
        case 3: {
            printf("����������: ");
            char bookName[maxBookName];
            scanf("%s", bookName);
            if (this->removeBookInBookshelf(this, bookName)) {
                printf("ɾ���ɹ�\n");
                system("pause");
            }
            break;
        }
        case 4:
            this->view->layer--;
            system("cls");
            break;
        case 5:
        default:
            return true;
    }

    return false;
}

bool runStudent(Controller this, int info) {
    switch (info) {
        case 1:
            printf("�ݲ�ͼ�飺\n");
            this->readBooks(this);
            system("pause");
            break;
        case 2: {
            printf("����������: ");
            char bookName[maxBookName];
            scanf("%s", bookName);
            this->borrowBook(this, bookName);
            break;
        }
        case 3: {
            printf("����������: ");
            char bookName[maxBookName];
            scanf("%s", bookName);
            this->returnBook(this, bookName);
            break;
        }
        case 4:
            this->view->layer--;
            system("cls");
            break;
        case 5:
        default:
            return true;
    }

    return false;
}

bool runViewer(Controller this, int info) {
    switch (info) {
        case 1:
            printf("�ݲ�ͼ�飺\n");
            this->readBooks(this);
            system("pause");
            break;
        case 2:
            this->view->layer--;
            system("cls");
            break;
        case 3:
        default:
            return true;
    }

    return false;
}

/**
 * ���ݲ�ͬ��layer���в�ͬ�Ĵ���
 * @param this
 * @param layer ��ǰ�˵��Ĳ���
 * @param info ִ�еĲ˵�����
 * @return �Ƿ��˳�����
 */
bool runInDifferentLayer(Controller this, int info) {
    if (this->view->layer == first) {
        switch (info) {
            case 1:
                this->user_login(this);
                this->view->layer++;
                system("cls");
                return false;
            case 0:
            default: // TODO �����Ƿ���Ҫ�ݴ���ƣ�
                return true;
        }
    } else { // layer == second
        assert(this->view->layer == second);

        // ֪�� layer==second �����ܽ�����⣬���ﻹ�÷�user����.
        // TODO ��ȫ��д��һ�𣬻����ٶȳ��� A���ٶȳ���
        switch (this->user->authority) {
            case root:
                return this->runRoot(this, info);
            case student:
                return this->runStudent(this, info);
            case viewer:
                return this->runViewer(this, info);
            default:
                return true;
        }
    }

}

/**
 * ϵͳ����������
 */
void run(Controller this) {
    bool isToStop = false;

    // TODO ����ͼ��ݺ�ĵ�һ��Ӧ��Ҫ���ļ��е��鼮����ϵͳ���ж�̬����
    this->loadBook(this, fopen("../books.txt", "r"));

    // ��������view��Ҫ֪��layer��controllerҲ��Ҫ
    while (!isToStop) {
        this->view->show(this->view, this->user);
        int info = 0;
        scanf("%d", &info);
        isToStop = this->runInDifferentLayer(this, info);
    }

    printf("--------END--------\n");
}

Controller new_controller() {
    // ��ʼ���ڴ�
    Controller controller = malloc(sizeof(struct controller));

    // ��ʼ������
    controller->setController = setController;
    controller->user_login = user_login;
    controller->borrowBook = borrowBook;
    controller->returnBook = returnBook;
    controller->showUserBorrowedBook = showUserBorrowedBook;
    controller->init_bookshelf = init_bookshelf;
    controller->readBooks = readBooks;
    controller->addBookToBookshelf = addBookToBookshelf;
    controller->findBookInBookshelf = findBookInBookshelf;
    controller->removeBookInBookshelf = removeBookInBookshelf;
    controller->loadBook = loadBook;
    controller->runInDifferentLayer = runInDifferentLayer;
    controller->runRoot = runRoot;
    controller->runStudent = runStudent;
    controller->runViewer = runViewer;
    controller->run = run;

    return controller;
}


#endif //LIBRARY_SYSTEM_CONTROLLER_H