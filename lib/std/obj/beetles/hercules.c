#include <globals.h>

inherit "/std/obj/beetle";

void create() {
    ::create();
    set_short("hercules");
    set_long("Known for it's incredible strength");
    set_ids(({"hercules", "beetle", "hercules beetle"}));
}