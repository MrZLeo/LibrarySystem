//
// Created by MrZ on 2020-11-01.
//

#include "Model/Book.h"
#include "Model/Bookshelf.h"

int main() {
    Bookshelf bookshelf = new_bookshelf();
    bookshelf->addBook(bookshelf, "Bible");
    bookshelf->addBook(bookshelf, "Price");
    bookshelf->addBook(bookshelf, "Awesome");
    bookshelf->showBook(bookshelf);
    bookshelf->removeBook(bookshelf, "Awesome");
    printf("%d\n", bookshelf->findBook(bookshelf, "Awesome"));
    printf("%d\n", bookshelf->getSize(bookshelf));
    printf("%d\n", bookshelf->isEmpty(bookshelf));
    bookshelf->showBook(bookshelf);
    return 0;
}