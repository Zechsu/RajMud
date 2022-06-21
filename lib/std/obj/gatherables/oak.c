#include <lib.h>

inherit LIB_RESOURCE;

void create() {
    ::create();
    set_short("%#604020%#oak%^RESET%^");
    set_long("It's %#604020%#oak timber%^RESET%^");
    set_ids(({"oak", "timber", "oak timber"}));
    set_resource("oak");
}