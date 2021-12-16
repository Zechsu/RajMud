#include <command.h>

int main(string str) {
    object tp = this_player();
    object ob;
    mixed result;

    if (!str) {
        return notify_fail("Open what?\n");
    }

    if (environment(tp)->is_door(str)) {
        result = ENV(tp)->query_door(str)->event_open();
        if (stringp(result)) {
            return notify_fail(result);
        }
        else {
            write("You open the door.\n");
            return 1;
        }
    }
    if (ob = present(str)) {
        result = ob->event_open();
        if (stringp(result)) {
            return notify_fail(result);
        }
        else {
            write("You open " + ob->query_short() + ".\n");
            return 1;
        }
    }
    else {
        write("Couldn't find anything to open.\n");
        return 1;
    }

    return 1;
}