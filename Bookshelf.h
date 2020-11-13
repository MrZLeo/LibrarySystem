//
// Created by MrZ on 2020-11-01.
//

#ifndef LIBRARY_SYSTEM_BOOKSHELF_H
#define LIBRARY_SYSTEM_BOOKSHELF_H

#include "Basic.h"
#include "Book.h"

/**
 * TODO：努力使用 跳表 实现 bookshelf 存储
 *
 */
typedef struct bookshelf {
    Book *root_book;
    int size;

    void (*free_Bookshelf)(struct bookshelf *);

    bool (*isEmpty)(struct bookshelf *);

    int (*getSize)(struct bookshelf *);

    Book (*findBook)(struct bookshelf *, char *);

    void (*showBook)(struct bookshelf *);

    void (*removeBook)(struct bookshelf *, int bookID);


} *Bookshelf;

Bookshelf new_bookshelf() {
    Bookshelf bookshelf = (Bookshelf) calloc(1, sizeof(struct bookshelf));
    bookshelf->root_book = NULL;
    bookshelf->size = 0;

    return bookshelf;
}

void free_Bookshelf(Bookshelf bookshelf) {
    bookshelf->root_book->free_Book(bookshelf->root_book);
    free(bookshelf);
}


#endif //LIBRARY_SYSTEM_BOOKSHELF_H
