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

    bool (*addBook)(struct bookshelf *, char *);

    int (*findBook)(struct bookshelf *, char *);

    void (*showBook)(struct bookshelf *);

    bool (*removeBook)(struct bookshelf *, char *bookName);

    void (*initBookshelf)(struct bookshelf *this, FILE *books);

    void (*storeBookshelf)(struct bookshelf *this, FILE *books);

} *Bookshelf;

static int ID = 1;

static void initBookshelf(Bookshelf this, FILE *books) {

    char bookName[maxBookName];
    while (fscanf(books, "%s", bookName)) {
        if (feof(books))
            break;
        this->addBook(this, bookName);
    }
    fclose(books);
}

static void storeBook(Book *book, FILE *books) {
    if (book == NULL)
        return;

    fprintf(books, "%s\n", book->name);
    storeBook(book->left, books);
    storeBook(book->right, books);
}

static void storeBookshelf(Bookshelf this, FILE *books) {
    storeBook(this->root_book, books);
}

void free_Bookshelf(Bookshelf this) {
    // FIXME
    free_Book(this->root_book, this->size);
    free(this);
}

static bool isEmpty(Bookshelf this) {
    return this->size == 0 ? true : false;
}

static int getSize(Bookshelf this) {
    return this->size;
}

static Book *addBook__(Bookshelf bookshelf, Book *book, int bookID, char *bookName) {

    if (book == NULL) {
        bookshelf->size++;
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

static bool addBook(Bookshelf bookshelf, char *bookName) {
    assert(bookshelf != NULL);
    int rootSize = bookshelf->size;
    bookshelf->root_book = addBook__(bookshelf, bookshelf->root_book, ID++, bookName);
    return rootSize + 1 == bookshelf->size;
}

static int findBook__(Book *book, char *bookName) {
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

static int findBook(Bookshelf this, char *bookName) {
    return findBook__(this->root_book, bookName);
}

static void showBook__(Book *book) {
    if (book == NULL)
        return;

    printf("bookName: 《%s》, bookID: %d\n", book->name, book->book_ID);
    showBook__(book->left);
    showBook__(book->right);

}

static void showBook(Bookshelf this) {
    showBook__(this->root_book);
}

static Book *findMax(Book *book) {
    Book *cur = book;

    while (cur->right != NULL)
        cur = cur->right;

    return cur;
}

static Book *removeMax(Bookshelf bookshelf, Book *book) {

    if (book->right == NULL) {
        Book *leftBook = book->left;
        free(book);
        bookshelf->size--;
        ID--;
        return leftBook;
    }

    book->right = removeMax(bookshelf, book->right);
    return book;
}

static Book *removeBook__(Bookshelf bookshelf, Book *book, char *bookName) {
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
        Book *maxBook = new_Book(findMax(book->left)->book_ID, findMax(book->left)->name);
        bookshelf->size++;

        maxBook->left = removeMax(bookshelf, book->left);
        maxBook->right = book->right;

        free(book);
        bookshelf->size--;

        return maxBook;
    }

}

static bool removeBook(Bookshelf this, char *bookName) {
    assert(this != NULL);
    int rootSize = this->size;
    this->root_book = removeBook__(this, this->root_book, bookName);
    return rootSize - 1 == this->size;
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
    bookshelf->initBookshelf = initBookshelf;
    bookshelf->storeBookshelf = storeBookshelf;

    return bookshelf;
}

#endif //LIBRARY_SYSTEM_BOOKSHELF_H
