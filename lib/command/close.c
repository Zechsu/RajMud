#include <command.h>

int main(string str) {
    object tp = this_player();
    object ob;
    
    if (!str) {
        return notify_fail("Close what?\n");
    }

    if (environment(tp)->is_door(str)) {
        return environment(tp)->query_door(str)->event_close();
    }

    ob = present(str, tp);
    if (!ob) ob = present(str, ENV(tp));
    
    if (ob) {
        return ob->event_close();
    }
    else {
        write("Couldn't find that.\n");
        return 1;
    }
}
