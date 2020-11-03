//
// Created by MrZ on 2020-11-03.
//

#ifndef LIBRARY_SYSTEM_CONTROLLER_H
#define LIBRARY_SYSTEM_CONTROLLER_H

#include "Basic.h"
#include "View.h"


typedef struct controller {

    View view;
    int listLength;
    char **menu;

    void (*setController)(View, int, char **);

    int (*getListLength)(struct controller);

    char **(*getMenu)(struct controller);

    void (*updateView)(struct controller);
} Controller;


#endif //LIBRARY_SYSTEM_CONTROLLER_H