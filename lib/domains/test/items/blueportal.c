#include <lib.h>

inherit LIB_PORTAL;

void create() {
    ::create();
    set_short("%^BLUE%^blue portal%^RESET%^");
    set_long("It leads to a beautiful lake.");
    set_ids(({"portal", "blue portal"}));
    set_destination("/domains/test/rooms/bedechka");
}