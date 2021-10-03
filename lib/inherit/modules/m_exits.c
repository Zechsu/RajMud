#include <globals.h>

private mapping exits = ([]);

void add_exit(string direction, string destination) {
    if (!exits[direction]) {
        exits[direction] = destination;
    }
}

void set_exits(mapping new_exits) {
    exits = new_exits;
}

void remove_exit(string exit) {
    if (exits[exit]) {
        map_delete(exits, exit);
    }
}

mapping query_exits() {
    return exits;
}

int add_door(string side, object door, string destination) {
    // Adds a door to an existing exit
    if (!destination) {
        if (exits[side]) {
            exits[side] = (["destination":exits[side], "door":door]);
            return 1;
        }
        debug_message("Side does not exist\n");
        return 0;
    }
    else {
        exits[side] = (["destination":destination, "door":door]);
        return 1;
    }
}

int is_door(string side) {
    if (mapp(exits[side])) {
        return 1;
    }
    else {
        return 0;
    }
}