#include <globals.h>

inherit LIB_CONTAINER;
inherit M_LOCK;
inherit M_OPEN;

void create() {
    ::create();
    set_short("chest");
    set_long("Test your lockpicking skills on it!");
    set_ids(({"chest"}));
    set_locked(1);
}