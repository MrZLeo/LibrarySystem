//
// Created by MrZ on 2020-11-01.
//

#ifndef LIBRARY_SYSTEM_BOOKSHELF_H
#define LIBRARY_SYSTEM_BOOKSHELF_H

#include "Basic.h"
#include "Book.h"

typedef struct bookshelf {
    Book *book;
    int size;

    void (*free_Bookshelf)(struct bookshelf *);
} Bookshelf;

void free_Bookshelf(Bookshelf *bookshelf) {
    bookshelf->book->free_Book(bookshelf->book);
    free(bookshelf);
}

#endif //LIBRARY_SYSTEM_BOOKSHELF_H
