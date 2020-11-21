//
// Created by MrZ on 2020-11-01.
//

#include "Controller/Controller.h"

int main() {
    Controller controller = new_controller();
    View view = new_view();
    User user = new_user();
    Bookshelf bookshelf = new_bookshelf();
    controller->setController(controller, view, bookshelf, user);

    controller->run(controller);
    return 0;
}