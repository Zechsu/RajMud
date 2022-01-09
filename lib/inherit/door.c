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

/**
 * @brief Add a side \n
 * If no `other_side` is given, then the side/exit will be one-way only.
 * 
 * @param side Direction of the exit
 * @param destination Where the door leads to
 * @param other_side Direction back to this room, based on the destination's room
 * @param room Destination room object
 * @return int 
 */
int add_side(string side, string destination, string other_side, object room) {
    if (!room) {
        room = previous_object();
    }
    // Add a door to the current room
    room->add_door(side, this_object(), destination);

    // Check if we have an other side to the door
    // Add the door exit to the destination
    // If no other_side is given then this side, will be one-way only.
    if (other_side) {
        destination->add_door(other_side, this_object(), room);
    }
    
    return 1;
}

/**
 * @brief Check if living can enter
 * 
 * @param who Living
 * @return int
 */
varargs int can_enter(object who) {
    if (!who) {
        who = this_player();
    }
    return 1;
}

/**
 * @brief Living has entered through door
 * 
 * @param from Which direction the living headed
 * @param who Living
 * @return int
 */
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

/**
 * @brief Checks if object is door
 * 
 * @return int 
 */
int is_door() {
    return 1;
}