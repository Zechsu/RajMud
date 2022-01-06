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
            if (exits[arg]["destination"]->event_enter(tp)) {
                int pos = tp->query_position();
                write(sprintf("You %s %s.\n", POSITION_D->query_you_move_action(pos), arg));
                say(sprintf("%s %s %s.\n", tp->query_name(), POSITION_D->query_other_move_action(pos), arg));
                tp->move(exits[arg]["destination"]);
                say(sprintf("%s %s from %s.\n", tp->query_name(), POSITION_D->query_other_move_action(pos), arg));
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
            int pos = tp->query_position();
            write(sprintf("You %s %s.\n", POSITION_D->query_you_move_action(pos), arg));
            say(sprintf("%s %s %s.\n", tp->query_name(), POSITION_D->query_other_move_action(pos), arg));
            tp->move(exits[arg]);
            say(sprintf("%s %s from %s.\n", tp->query_name(), POSITION_D->query_other_move_action(pos), arg));
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
