//
// Created by MrZ on 2020-11-03.
//
#include "Basic.h"
#include "Controller.h"

int getListLength(Controller controller) {
    return controller.listLength;
}

char **getMenu(Controller controller) {
    return controller.menu;
};

void updateView(Controller controller) {
    controller.view.viewMenu((const char **) controller.menu, controller.listLength);
};