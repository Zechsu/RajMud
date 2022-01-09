/**
 * @file portal.c
 * @author Rajo (zechsnox@gmail.com)
 * @brief Base objects for portals
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <globals.h>

inherit BASE;
inherit M_DESC;
inherit M_VISIBLE;

//! Where the portal leads to
private string destination;

void create() {
    ::create();
    set_short("portal");
    set_long("It's a portal leading to somewhere.");
    set_ids(({"portal"}));
}

void init() {
    add_action("event_enter", "enter");
}

/**
 * @brief Set where the portal leads to
 * 
 * @param dest Room file
 */
void set_destination(string dest) {
    if (load_object(dest)) {
        destination = dest;
    }
}

/**
 * @brief Returns destination of portal
 * 
 * @return string Room file
 */
string query_destination() {
    return destination;
}

/**
 * @brief Checks if living can enter
 * 
 * @param who Living
 * @return int 
 */
int can_enter(object who) {
    return 1;
}

/**
 * @brief Living entered portal
 * 
 * @param args Name (used for id-ing the portal)
 * @return int 
 */
int event_enter(string args) {
    object who;
    if (!args) {
        return 0;
    }
    if (member_array(args, query_ids()) == -1) {
        return 0;
    }
    who = this_player();
    if (!can_enter(who)) {
        return 0;
    }
    who->event_move(query_destination());
    write("You enter " + query_short() + "\n");
    say(sprintf("%s enters %s", who->query_short(), query_short()));
    return 1;
}

/**
 * @brief Checks if object is portal
 * 
 * @return int 
 */
int is_portal() {
    return 1;
}