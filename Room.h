//
// Created by MrZ on 2020-11-02.
//

#ifndef LIBRARY_SYSTEM_ROOM_H
#define LIBRARY_SYSTEM_ROOM_H

#include "Basic.h"
#include "Bookshelf.h"
#include "Book.h"

typedef struct room {
    Bookshelf *bookshelf;
    int roomNumber;

    struct room *(*new_Room)();

    void (*free_Room)(struct room *);
} Room;

Room *new_Room() {
    Room *room = (Room *) calloc(1, sizeof(Room));
    return room;
}

void free_Room(Room *room) {
    room->bookshelf->free_Bookshelf(room->bookshelf);
    free(room);
}

#endif //LIBRARY_SYSTEM_ROOM_H
