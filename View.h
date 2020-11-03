//
// Created by MrZ on 2020-11-03.
//

#ifndef LIBRARY_SYSTEM_VIEW_H
#define LIBRARY_SYSTEM_VIEW_H

#include "Basic.h"

typedef struct view {
    void (*viewMenu)(const char **, int);
} View;


#endif //LIBRARY_SYSTEM_VIEW_H
