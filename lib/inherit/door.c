/**
 * @file door.c
 * @author Rajo (zechsnox@gmail.com)
 * @brief Base door object
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <globals.h>

inherit M_DESC;
inherit M_OPEN;
inherit M_LOCK;

private mapping destinations = ([]);

void create() {
    ::create();
}

/**
 * Checks if living can enter.
 * 
 * @param {object} who - The living (if not provided set to `this_player()`)
 * @return {int} 1 if can enter.
 */
varargs int can_enter(object who) {
    if (!who) {
        who = this_player();
    }
    if (!is_open()) {
        return notify_fail("It's closed.\n");
    }
    return 1;
}

/**
 * Should fire when a living enters through a door.
 * 
 * @param {string} direction - From which direction the living headed.
 * @param {object} who - The living who did it.
 * @return Returns 1 if everything went sucessfully. 0 if the living can't enter.
 */
varargs int event_enter(string direction, object who) {
    int pos;
    object env;
    mapping exits;
    string inverse = invert_cardinal_direction(direction, 1);
    if (!who) {
        who = this_player();
    }
    if (!can_enter(who)) {
        return 0;
    }
    pos = who->query_position();
    env = environment(who);
    exits = env->query_exits();

    // Write messages for going
    write(sprintf("You %s %s.\n", POSITION_D->query_you_move_action(pos), direction));
    say(sprintf("%s %s %s.\n", who->query_name(), POSITION_D->query_other_move_action(pos), direction));

    who->event_move(destinations[direction]);

    // Message when arrived
    say(sprintf("%s %s from %s.\n", who->query_name(), POSITION_D->query_other_move_action(pos), inverse));
    who->force_me("look");
    return 1;
}

/**
 * Checks if object is door.
 * 
 * @return Returns 1 if it a door.
 */
int is_door() {
    return 1;
}

void set_destination(string direction, string dest) {
    destinations[direction] = dest;
}

string query_destination(string direction) {
    return destinations[direction];
}