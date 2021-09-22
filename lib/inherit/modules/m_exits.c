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