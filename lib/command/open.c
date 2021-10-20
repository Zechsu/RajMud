#include <command.h>

int main(string str) {
    object tp = this_player();

    if (!str) {
        return notify_fail("Open what?\n");
    }

    if (environment(tp)->is_door(str)) {
        if (environment(tp)->query_exits()[str]["door"]->event_open()) {
            write("You open the door.\n");
            return 1;
        }
        else {
            write("The door is already opened.\n");
            return 1;
        }
    }
    else {
        write("Couldn't find anything to open.\n");
        return 1;
    }

    return 1;
}