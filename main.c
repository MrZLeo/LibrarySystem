//
// Created by MrZ on 2020-11-01.
//

#include "Basic.h"
#include "Book.h"

int main() {
    Book book = {1, "Bible", getID, getName};
    printf("%s", book.getName(book));
    return 0;
}