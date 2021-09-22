#include <globals.h>

inherit LIB_ITEM;

void create() {
    ::create();
    set_short("knife");
    set_long("Watch out, it's pointy!");
    set_ids(({"knife"}));
    set_message("on_ground", "a $N is on the ground.");
}