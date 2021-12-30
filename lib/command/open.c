#include <command.h>

int main(string str) {
    object tp = this_player();
    object ob;

    if (!str) {
        return notify_fail("Open what?\n");
    }

    if (ENV(tp)->is_door(str)) {
        return ENV(tp)->query_door(str)->event_open();
    }
    
    ob = present(str, tp);
    if (!ob) ob = present(str, ENV(tp));
    if (ob) {
        return ob->event_open();
    }
    else {
        write("Couldn't find anything to open.\n");
        return 1;
    }

    return 1;
}