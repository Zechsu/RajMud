#include <command.h>

int main(string arg) {
    object tp = this_player();
    mapping exits = environment(tp)->query_exits();

    if (!arg) {
        return notify_fail("Go where?\n");
    }

    if (environment(tp)->is_door(arg)) {
        if (exits[arg]["door"]->is_open()) {
            if (exits[arg]["destination"]->event_enter(tp)) {
                write("You walk " + arg + ".\n");
                say(tp->query_name() + " heads " + arg + "\n");
                tp->move(exits[arg]["destination"]);
                say(tp->query_name() + " comes from " + arg + "\n");
                tp->call_verb("look", "");
                return 1;
            }
            else {
                return notify_fail("You cannot go there.\n");
            }
        }
        else {
            return notify_fail("It is closed.\n");
        }
    }
    else if (member_array(arg, keys(exits)) != -1) {
        if (exits[arg]->event_enter()) {
            write("You walk " + arg + ".\n");
            say(tp->query_name() + " heads " + arg + "\n");
            tp->move(exits[arg]);
            say(tp->query_name() + " comes from " + arg + "\n");
            tp->call_verb("look", "");
            return 1;
        }
        else {
            return notify_fail("You cannot go there.\n");
        }
    }
    else {
        write("No such exit.\n");
    }
    return 1;
}
