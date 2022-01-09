#include <command.h>

int main(string str) {
    object tp = this_player();
    object ob;

    if (!str) {
        return notify_fail("Open what?\n");
    }
    
    ob = environment(tp)->query_door(str);
    if (ob) {
        return ob->event_open(tp);
    }
    
    ob = present(str, tp);
    if (!ob) ob = present(str, ENV(tp));
    if (ob) {
        return ob->event_open(tp);
    }
    else {
        write("Couldn't find that.\n");
        return 1;
    }

    return 1;
}