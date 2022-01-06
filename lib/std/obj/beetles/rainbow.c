#include "colors.h"

inherit "std/obj/beetle";

void create() {
    ::create();
    set_short(make_rainbow("rainbow"));
    set_long("A beetle that has captured the magic of the rainbow in it's shell.");
    set_ids(({"rainbow", "rainbow", "beetle"}));
}
