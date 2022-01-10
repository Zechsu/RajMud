/**
 * @file room.c
 * @author Rajo (zechsnox@gmail.com)
 * @brief Base room object
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <modules.h>
#include <lib.h>

inherit M_DESC;
inherit M_EXITS;

void create() {}

/**
 * @brief Adds an item inside the room
 * 
 * @param item Item
 */
void add_item(mixed item) {
    item->move(this_object());
    return;
}

/**
 * @brief Adds a prop inside the room
 * 
 * @param prop Prop name
 * @param desc Prop description
 */
void add_prop(string prop, string desc) {
    object ob = new(LIB_PROP);
    ob->set_id(prop);
    ob->set_long(desc);
    ob->move(this_object());
}

/**
 * @brief Returns all props inside the room
 * 
 * @return object* Props
 */
object* query_props() {
    return filter_array(all_inventory(this_object()), (: $1->is_prop() :));
}

/**
 * @brief Returns all items objects inside the room that are not living
 * 
 * @return object* Items
 */
object* query_items() {
    object* ret = all_inventory(this_object());
    ret = filter_array(ret, (: !living($1) :));
    ret = filter_array(ret, (: !$1->is_prop() :));
    return ret;
}

/**
 * @brief Checks if living can go
 * 
 * @param who Living
 * @return int 
 */
int can_go(object who) {
    return 1;
}

/**
 * @brief Living went at exit
 * 
 * @param direction Exit direction
 * @param who Living
 * @return int 
 */
varargs int event_go(string direction, object who) {
    int pos;
    mapping exits = query_exits();
    string inverse = invert_cardinal_direction(direction, 1);
    object door;

    if (!who) {
        who = this_player();
    }

    // If direction leads to a door, call the door's event_enter
    if (door = query_door(direction)) {
        return door->event_enter(direction, who);
    }

    pos = who->query_position();

    // Write messages for going
    write(sprintf("You %s %s.\n", POSITION_D->query_you_move_action(pos), direction));
    say(sprintf("%s %s %s.\n", who->query_name(), POSITION_D->query_other_move_action(pos), direction));

    who->event_move(exits[direction]);

    // Write message when arrived
    say(sprintf("%s %s from %s.\n", who->query_name(), POSITION_D->query_other_move_action(pos), inverse));
    who->call_verb("look", "");
    return 1;
}

void add_door(string short, string side, string dest, mixed flag) {
    object door = new(LIB_DOOR);

    // Set up the door
    set_exit(side, door);
    door->set_destination(side, dest);
    door->set_short(short);

    // If flag is integer, use inverted direction
    if (intp(flag)) {
        if (dest->query_door(invert_cardinal_direction(side))) {
            Log("debug", sprintf("Tried to add a door to already existing one at %O side %s to room %s", this_object(), side, dest));
            return;
        }
        dest->set_exit(invert_cardinal_direction(side), door);
        door->set_destination(invert_cardinal_direction(side), file_name(this_object()));
    }
    // Else, if given a specific direction, use that one
    else if (stringp(flag)) {
        // If destination already has a room, don't add any
        if (dest->query_door(flag)) {
            Log("debug", sprintf("Tried to add a door to already existing one at %O side %s to room %s", this_object(), side, dest));
            return;
        }
        dest->set_exit(flag, door);
        // Change destination with file_name, since this will change "current_dest" variable to a string which can be saved
        door->set_destination(flag, file_name(this_object()));
    }
}