#include <lib.h>
#include <daemons.h>

inherit LIB_ITEM;

void create() {
    ::create();
    set_short("compass");
    set_ids(({"compass"}));
}

string query_long() {
    object env = environment(this_player());
    if (env->query_virtual_room()) {
        return "You are at " + env->query_x() + ", " + env->query_y() + ".";
    }
    return "It's a compass!";
}