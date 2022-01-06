#include <globals.h>

inherit "/std/obj/beetle";

void create() {
    ::create();
    set_short("stag");
    set_long("This is what we would get if we were to shrink a deer.");
    set_ids(({"beetle", "stag", "stag beetle"}));
    set_skill_level("attack", 10);
}
