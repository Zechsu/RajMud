#include <command.h>

int main(string str) {
    object tp = this_player();

    if (!str) {
        return notify_fail("Close what?\n");
    }

    if (environment(tp)->is_door(str)) {
        if (environment(tp)->query_exits()[str]["door"]->close()) {
            write("You close the door.\n");
            return 1;
        }
        else {
            write("The door is already closed.\n");
            return 1;
        }
    }
    else {
        write("Couldn't find anything to close.\n");
        return 1;
    }
}
