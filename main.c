//
// Created by MrZ on 2020-11-01.
//

#include "Book.h"
#include "Bookshelf.h"

int main() {
    Bookshelf bookshelf = new_bookshelf();
    bookshelf->addBook(bookshelf, 1, "Bible");
    bookshelf->addBook(bookshelf, 2, "Price");
    bookshelf->addBook(bookshelf, 3, "Awesome");
    bookshelf->showBook(bookshelf);
    return 0;
}