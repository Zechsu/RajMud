#include <command.h>

int main(string arg) {
    object tp = this_player();
    mapping exits = environment(tp)->query_exits();
    if (!arg) {
        write("Go where?\n");
    }
    else if (member_array(arg, keys(exits)) != -1) {
        write("You walk " + arg + ".\n");
        say(tp->query_name() + " heads " + arg + "\n");
        tp->move(exits[arg]);
        say(tp->query_name() + " comes from " + arg + "\n");
        tp->call_verb("look", "");
    }
    else {
        write("No such exit.\n");
    }
    return 1;
}
