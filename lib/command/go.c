#include <command.h>

int main(string arg) {
    mapping exits = environment(this_player())->query_exits();
    if (!arg) {
        write("Go where?\n");
    }
    else if (member_array(arg, keys(exits)) != -1) {
        write("You walk " + arg + ".\n");
        this_player()->move(exits[arg]);
    }
    else {
        write("No such exit.\n");
    }
    return 1;
}