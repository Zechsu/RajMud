#include <globals.h>

inherit M_OPEN;
inherit M_LOCK;

int is_opened = 0;

int add_side(string side, string destination, string other_side, object room) {
    if (!room) {
        room = previous_object();
    }

    room->add_door(side, this_object(), destination);

    if (other_side) {
        destination->add_door(other_side, this_object(), room);
    }
    
    return 1;
}

varargs int can_enter(object who) {
    if (!who) {
        who = this_player();
    }
    return 1;
}

varargs int event_enter(string from, object who) {
    int pos;
    object env;
    mapping exits;
    string inverse = invert_cardinal_direction(from);
    if (!who) {
        who = this_player();
    }
    if (!can_enter(who)) {
        return 0;
    }
    pos = who->query_position();
    env = environment(who);
    exits = env->query_exits();

    write(sprintf("You %s %s.\n", POSITION_D->query_you_move_action(pos), from));
    say(sprintf("%s %s %s.\n", who->query_name(), POSITION_D->query_other_move_action(pos), from));
    who->event_move(exits[from]["destination"]);
    say(sprintf("%s %s from %s.\n", who->query_name(), POSITION_D->query_other_move_action(pos), inverse));
    who->call_verb("look", "");
    return 1;
}

int is_door() {
    return 1;
}