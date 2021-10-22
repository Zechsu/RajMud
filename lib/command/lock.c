#include <command.h>

int main(string str) {
    object tp = this_player();
    mixed door;
    if (!str) {
        return notify_fail("Lock what?\n");
    }
    if (ENV(tp)->is_door(str)) {
        door = ENV(tp)->query_exits()[str]["door"]->event_lock(tp);
        if (stringp(door)) {
            return notify_fail(door);
        }
        else {
            write("You lock the door.\n");
            return 1;
        }
    }
    
    return notify_fail("Can't find that.\n");
}