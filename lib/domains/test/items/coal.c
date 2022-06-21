#include <lib.h>

inherit LIB_RESOURCE;

void create() {
    ::create();
    set_short("%#949494%#coal%^RESET%^");
    set_long("It's a lump of %#949494%#coal%^RESET%^");
    set_ids(({"coal"}));
    set_resource("coal");
}