//
// Created by MrZ on 2020-11-01.
//

#ifndef LIBRARY_SYSTEM_BOOK_H
#define LIBRARY_SYSTEM_BOOK_H

#include "Basic.h"

typedef struct book {
    int book_ID;
    char *name;

    int (*getID)(struct book book);

    char *(*getName)(struct book book);
} Book;

int getID(Book book) {
    return book.book_ID;
}

char *getName(Book book) {
    return book.name;
}

#endif //LIBRARY_SYSTEM_BOOK_H
