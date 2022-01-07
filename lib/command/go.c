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
            // if (exits[arg]["destination"]->can_enter(tp)) {
            //     int pos = tp->query_position();
            //     write(sprintf("You %s %s.\n", POSITION_D->query_you_move_action(pos), arg));
            //     say(sprintf("%s %s %s.\n", tp->query_name(), POSITION_D->query_other_move_action(pos), arg));
            //     tp->event_move(exits[arg]["destination"]);
            //     say(sprintf("%s %s from %s.\n", tp->query_name(), POSITION_D->query_other_move_action(pos), arg));
            //     tp->call_verb("look", "");
            //     return 1;
            // }
            // else {
            //     return notify_fail("You cannot go there.\n");
            // }
        }
        else {
            return notify_fail("It is closed.\n");
        }
    }
    else if (member_array(arg, keys(exits)) != -1) {
        return environment(tp)->event_go(arg, tp);
        // if (exits[arg]->event_go()) {
        //     string inverse = invert_cardinal_direction(arg);
        //     int pos = tp->query_position();
        //     write(sprintf("You %s %s.\n", POSITION_D->query_you_move_action(pos), arg));
        //     say(sprintf("%s %s %s.\n", tp->query_name(), POSITION_D->query_other_move_action(pos), arg));
        //     tp->event_move(exits[arg]);
        //     say(sprintf("%s %s from %s.\n", tp->query_name(), POSITION_D->query_other_move_action(pos), inverse));
        //     tp->call_verb("look", "");
        //     return 1;
        // }
        // else {
        //     return notify_fail("You cannot go there.\n");
        // }
    }
    else {
        write("No such exit.\n");
    }
    return 1;
}
