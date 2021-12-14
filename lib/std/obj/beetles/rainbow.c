#include "colors.h"

inherit "std/obj/beetle";

void create() {
    ::create();
    set_short(make_rainbow("rainbow beetle"));
    set_ids(({"rainbow", "rainbow", "beetle"}));
}
