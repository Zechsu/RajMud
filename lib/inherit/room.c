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

void create() {

}

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
    string inverse = invert_cardinal_direction(direction);
    if (!who) {
        who = this_player();
    }
    pos = who->query_position();
    write(sprintf("You %s %s.\n", POSITION_D->query_you_move_action(pos), direction));
    say(sprintf("%s %s %s.\n", who->query_name(), POSITION_D->query_other_move_action(pos), direction));
    who->event_move(exits[direction]);
    say(sprintf("%s %s from %s.\n", who->query_name(), POSITION_D->query_other_move_action(pos), inverse));
    who->call_verb("look", "");
    return 1;
}