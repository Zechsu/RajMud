#include <command.h>

int main(string arg) {
    if (this_player()->is_in_combat()) {
        this_player()->stop_combat();
        tell_object(this_player(), "You stop attacking.\n");
    }
    else {
        return notify_fail("You're not in combat!\n");
    }
    return 1;
}