//
// Created by MrZ on 2020-11-03.
//

#ifndef LIBRARY_SYSTEM_CONTROLLER_H
#define LIBRARY_SYSTEM_CONTROLLER_H

#include "Basic.h"
#include "View.h"
#include "User.h"
#include "Bookshelf.h"


typedef struct controller {

    View *view;
    User *user;
    Bookshelf *bookshelf;

    void (*setController)(struct controller *this, View *view, Bookshelf *bookshelf, User *user);

    void (*updateView)(struct controller *this);

} *Controller;

void setController(Controller this, View *view, Bookshelf *bookshelf, User *user) {
    this->view = view;
    this->bookshelf = bookshelf;
    this->user = user;
}

void updateView(Controller this) {
    this->view->updateDetail(this->view);
}

#endif //LIBRARY_SYSTEM_CONTROLLER_H