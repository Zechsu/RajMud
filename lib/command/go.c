#include <globals.h>
#include <command.h>

int main(string arg) {
    object tp = this_player();
    mapping exits = environment(tp)->query_exits();

    if (!arg) {
        return notify_fail("Go where?\n");
    }

    else if (member_array(arg, keys(exits)) != -1) {
        return environment(tp)->event_go(arg, tp);
    }
    else {
        write("No such exit.\n");
    }
    return 1;
}
