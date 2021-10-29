#include <command.h>

int main(string str) {
    object tp = this_player();
    mixed result;
    object ob;
    
    if (!str) {
        return notify_fail("Close what?\n");
    }

    if (environment(tp)->is_door(str)) {
        if (environment(tp)->query_exits()[str]["door"]->event_close()) {
            write("You close the door.\n");
            return 1;
        }
        else {
            write("The door is already closed.\n");
            return 1;
        }
    }
    if (ob = present(str)) {
        result = ob->event_close();
        if (stringp(result)) {
            return notify_fail(result);
        }
        else {
            write("You close " + ob->query_short() + ".\n");
            return 1;
        }
    }
    else {
        write("Couldn't find that.\n");
        return 1;
    }
}
