#include <globals.h>

inherit "/std/obj/beetle";

void create() {
    ::create();
    set_short("rhinoceros");
    set_long("Known for it's distinct rhino-looking horn");
    set_ids(({"rhino", "rhinoceros", "beetle", "rhino beetle", "rhinoceros beetle"}));
}