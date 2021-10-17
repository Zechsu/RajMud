#include <globals.h>

inherit LIB_CONTAINER;

void create() {
    ::create();
    set_short("plastic bag");
    set_long("It's a regular old plastic bag.");
    set_ids(({"bag", "plastic bag"}));
}