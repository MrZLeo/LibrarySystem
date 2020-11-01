//
// Created by MrZ on 2020-11-01.
//

#ifndef LIBRARY_SYSTEM_BOOK_H
#define LIBRARY_SYSTEM_BOOK_H

typedef struct book {
    int book_ID;
    char *name;

    int (*getID)(struct book book);
    char *(*getName)(struct book book);
} Book;

#endif //LIBRARY_SYSTEM_BOOK_H
