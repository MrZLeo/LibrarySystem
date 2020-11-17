//
// Created by MrZ on 2020-11-01.
//

#ifndef LIBRARY_SYSTEM_BOOKSHELF_H
#define LIBRARY_SYSTEM_BOOKSHELF_H

#include "Basic.h"
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

    void (*addBook)(struct bookshelf *, int, char *);

    int (*findBook)(struct bookshelf *, char *);

    void (*showBook)(struct bookshelf *);

    void (*removeBook)(struct bookshelf *, char *bookName);


} *Bookshelf;

void free_Bookshelf(Bookshelf bookshelf) {
    bookshelf->root_book->free_Book(bookshelf->root_book);
    free(bookshelf);
}

bool isEmpty(Bookshelf bookshelf) {
    return bookshelf->size == 0;
}

int getSize(Bookshelf bookshelf) {
    return bookshelf->size;
}

// TODO ʵ�ַ��������⣬Ҫ�ĳ�return Node�ķ���
Book *addBook__(Bookshelf bookshelf, Book *book, int bookID, char *bookName) {

    if (book == NULL) {
        bookshelf->size++;
        printf("��ӳɹ�\n");
        return new_Book(bookID, bookName);
    }

    if (strcmp(book->name, bookName) > 0)
        book->left = addBook__(bookshelf, book->left, bookID, bookName);
    else if (strcmp(book->name, bookName) < 0)
        book->right = addBook__(bookshelf, book->right, bookID, bookName);
    else // ==
        printf("�����Ѵ���\n");
}

void addBook(Bookshelf bookshelf, int bookID, char *bookName) {
    assert(bookshelf != NULL);
    bookshelf->root_book = addBook__(bookshelf, bookshelf->root_book, bookID, bookName);
}

int findBook__(Book *book, char *bookName) {
    if (book == NULL)
        printf("�Ҳ�������\n");

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
        printf("�Ҳ����Ȿ��\n");
        return NULL;
    }

    if (strcmp(book->name, bookName) < 0) {
        book->right = removeBook__(bookshelf, book->right, bookName);
        return book;
    } else if (strcmp(book->name, bookName) > 0) {
        book->left = removeBook__(bookshelf, book->right, bookName);
        return book;
    } else {

        // ������ɾ������
        if (book->left == NULL) {
            Book *rightBook = book->right;
            free(book);
            bookshelf->size--;
            return rightBook;
        }
        if (book->left == NULL) {
            Book *leftBook = book->left;
            free(book);
            bookshelf->size--;
            return leftBook;
        }

        // ���Ҷ���Ϊ��
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
    // �����ڴ�ռ�
    Bookshelf bookshelf = (Bookshelf) calloc(1, sizeof(struct bookshelf));

    // ��ʼ������
    bookshelf->root_book = NULL;
    bookshelf->size = 0;

    // ��ʼ������
    bookshelf->getSize = getSize;
    bookshelf->isEmpty - isEmpty;
    bookshelf->free_Bookshelf = free_Bookshelf;
    bookshelf->addBook = addBook;
    bookshelf->findBook = findBook;
    bookshelf->showBook = showBook;
    bookshelf->removeBook = removeBook;

    return bookshelf;
}
#endif //LIBRARY_SYSTEM_BOOKSHELF_H
