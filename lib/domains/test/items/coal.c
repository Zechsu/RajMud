#include <globals.h>

inherit LIB_RESOURCE;

void create(int w) {
    ::create();
    set_short("%#949494%#coal%^RESET%^");
    set_long("It's a lump of %#949494%#coal%^RESET%^");
    set_ids(({"coal"}));
    set_resource("coal");
    add_weight(w);
}