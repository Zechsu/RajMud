#include <globals.h>
#include <command.h>

int main(string arg) {
    object tp = this_player();
    mapping exits = environment(tp)->query_exits();

    if (!arg) {
        return notify_fail("Go where?\n");
    }

    if (environment(tp)->is_door(arg)) {
        if (exits[arg]["door"]->is_open()) {
            return exits[arg]["door"]->event_enter(arg, tp);
        }
        else {
            return notify_fail("It is closed.\n");
        }
    }
    else if (member_array(arg, keys(exits)) != -1) {
        return environment(tp)->event_go(arg, tp);
    }
    else {
        write("No such exit.\n");
    }
    return 1;
}
