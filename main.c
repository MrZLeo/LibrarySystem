//
// Created by MrZ on 2020-11-01.
//

#include "Basic.h"
#include "Book.h"
#include "View.h"
#include "Controller.h"

int main() {
    Controller controller;
    View *view = (View *) malloc(sizeof(struct view));
    controller.setController(*view, listLength, (char **) menu);
    controller.updateView(controller);
    return 0;
}