//
// Created by MrZ on 2020-11-01.
//

#ifndef LIBRARY_SYSTEM_BOOKSHELF_H
#define LIBRARY_SYSTEM_BOOKSHELF_H

#include "../Basic.h"
#include "Book.h"
#include <assert.h>

/**
 * @author Mr.Z
 *
 */
typedef struct bookshelf {
    Book *root_book;
    int size;

    void (*free_Bookshelf)(struct bookshelf *);

    bool (*isEmpty)(struct bookshelf *);

    int (*getSize)(struct bookshelf *);

    void (*addBook)(struct bookshelf *, char *);

    int (*findBook)(struct bookshelf *, char *);

    void (*showBook)(struct bookshelf *);

    void (*removeBook)(struct bookshelf *, char *bookName);

    void (*setID)(struct bookshelf *this);

    void (*initBookshelf)(struct bookshelf *this);

} *Bookshelf;

static int ID = 1;

void setID(Bookshelf this) {
    ID = this->size + 1;
}

// TODO 读取文件中的书籍资料
void initBookshelf(Bookshelf this) {

}

void free_Bookshelf(Bookshelf this) {
    free_Book(this->root_book, this->size);
    free(this);
}

bool isEmpty(Bookshelf this) {
    return this->size == 0 ? true : false;
}

int getSize(Bookshelf this) {
    return this->size;
}

Book *addBook__(Bookshelf bookshelf, Book *book, int bookID, char *bookName) {

    if (book == NULL) {
        bookshelf->size++;
        printf("添加成功\n");
        return new_Book(bookID, bookName);
    }

    if (strcmp(book->name, bookName) > 0)
        book->left = addBook__(bookshelf, book->left, bookID, bookName);
    else if (strcmp(book->name, bookName) < 0)
        book->right = addBook__(bookshelf, book->right, bookID, bookName);
    else {
        printf("本书已存在\n");
    }

    return book;
}

void addBook(Bookshelf bookshelf, char *bookName) {
    assert(bookshelf != NULL);
    bookshelf->root_book = addBook__(bookshelf, bookshelf->root_book, ID++, bookName);
}

int findBook__(Book *book, char *bookName) {
    if (book == NULL) {
        printf("找不到该书\n");
        return -1;
    }

    if (strcmp(book->name, bookName) == 0) {
        return book->book_ID;
    } else if (strcmp(book->name, bookName) < 0) {
        return findBook__(book->right, bookName);
    } else {    // > 0
        return findBook__(book->left, bookName);
    }

}

int findBook(Bookshelf this, char *bookName) {
    return findBook__(this->root_book, bookName);
}

void showBook__(Book *book) {
    if (book == NULL)
        return;

    printf("bookName: %s, bookID: %d\n", book->name, book->book_ID);
    showBook__(book->left);
    showBook__(book->right);

}

void showBook(Bookshelf this) {
    showBook__(this->root_book);
}

Book *findMax(Book *book) {
    Book *cur = book;

    while (cur->right != NULL)
        cur = cur->right;

    return cur;
}

void removeMax(Bookshelf bookshelf, Book *book) {
    Book *maxBook = findMax(book);
    free(maxBook);
    bookshelf->size--;
}

Book *removeBook__(Bookshelf bookshelf, Book *book, char *bookName) {
    if (book == NULL) {
        return NULL;
    }

    if (strcmp(book->name, bookName) < 0) {
        book->right = removeBook__(bookshelf, book->right, bookName);
        return book;
    } else if (strcmp(book->name, bookName) > 0) {
        book->left = removeBook__(bookshelf, book->left, bookName);
        return book;
    } else {

        // 真正的删除操作
        if (book->left == NULL) {
            Book *rightBook = book->right;
            free(book);
            bookshelf->size--;
            return rightBook;
        }
        if (book->right == NULL) {
            Book *leftBook = book->left;
            free(book);
            bookshelf->size--;
            return leftBook;
        }

        // 左右都不为空
        Book *maxBook = findMax(book->left);
        maxBook = new_Book(maxBook->book_ID, maxBook->name);
        bookshelf->size++;

        removeMax(bookshelf, book);
        maxBook->left = book->left;
        maxBook->right = book->right;

        free(book);
        bookshelf->size--;

        return maxBook;
    }

}

void removeBook(Bookshelf this, char *bookName) {
    assert(this != NULL);

    this->root_book = removeBook__(this, this->root_book, bookName);
}


Bookshelf new_bookshelf() {
    // 申请内存空间
    Bookshelf bookshelf = (Bookshelf) calloc(1, sizeof(struct bookshelf));

    // 初始化参数
    bookshelf->root_book = NULL;
    bookshelf->size = 0;

    // 初始化函数
    bookshelf->getSize = getSize;
    bookshelf->isEmpty = isEmpty;
    bookshelf->free_Bookshelf = free_Bookshelf;
    bookshelf->addBook = addBook;
    bookshelf->findBook = findBook;
    bookshelf->showBook = showBook;
    bookshelf->removeBook = removeBook;
    bookshelf->setID = setID;

    return bookshelf;
}

#endif //LIBRARY_SYSTEM_BOOKSHELF_H
