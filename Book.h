//
// Created by MrZ on 2020-11-01.
//

#ifndef LIBRARY_SYSTEM_BOOK_H
#define LIBRARY_SYSTEM_BOOK_H

#include "Basic.h"

typedef struct book {
    int book_ID;
    char *name;

    struct book *left;
    struct book *right;

    void (*free_Book)(struct book *);

    int (*getID)(struct book book);

    char *(*getName)(struct book book);

} Book;

Book *new_Book(int ID, char *name) {
    Book *book = (Book *) calloc(1, sizeof(Book));
    book->book_ID = ID;
    book->name = name;
    book->left = NULL;
    book->right = NULL;
    return book;
}

// TODO: 重新思考free操作的内存问题
void free_Book(Book *book) {
    free(book->name);
    free_Book(book);
}

int getID(Book *book) {
    return book->book_ID;
}

char *getName(Book *book) {
    return book->name;
}

#endif //LIBRARY_SYSTEM_BOOK_H
