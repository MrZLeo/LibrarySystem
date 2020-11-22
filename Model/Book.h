//
// Created by MrZ on 2020-11-01.
//

#ifndef LIBRARY_SYSTEM_BOOK_H
#define LIBRARY_SYSTEM_BOOK_H

#include "../Basic.h"
#include <assert.h>

typedef struct book {
    int book_ID;
    char *name;

    struct book *left;
    struct book *right;

} Book;

Book *new_Book(int ID, char *name) {
    Book *book = (Book *) calloc(1, sizeof(Book));
    book->book_ID = ID;

    // ��char*Ҫ��һ������
    book->name = malloc(sizeof(char) * strlen(name));
    strcpy(book->name, name);

    book->left = NULL;
    book->right = NULL;

    return book;
}

// TODO: ����˼��free�������ڴ�����
void free_Book(Book *book, int size) {
    assert(book != NULL);
    for (int i = 0; i < size; ++i) {
        free(book->name);
        free(book);
    }
}

#endif //LIBRARY_SYSTEM_BOOK_H
