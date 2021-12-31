#include <globals.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    set_short("chest");
    set_long("Test your lockpicking skills on it!");
    set_ids(({"chest"}));
    set_locked(1);
}