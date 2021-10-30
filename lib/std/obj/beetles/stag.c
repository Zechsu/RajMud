#include <globals.h>

inherit "/std/obj/beetle";

void create() {
    ::create();
    set_short("stag beetle");
    set_long("It's a lovely stag beetle!");
    set_ids(({"beetle", "stag", "stag beetle"}));
}
