//
// Created by MrZ on 2020-11-01.
//

#ifndef LIBRARY_SYSTEM_BASIC_H
#define LIBRARY_SYSTEM_BASIC_H

#include <stdio.h>
#include <stdlib.h>
#include "Book.h"
#include "Bookshelf.h"

typedef enum bool {
    true = 1,
    false = 0,
} bool;

typedef struct Tree {
    int part;
    Book book;
    int size;

    bool (*isEmpty)(struct Tree *tree);
    int (*getSize)(struct Tree *tree);
} *Tree;

#endif //LIBRARY_SYSTEM_BASIC_H
