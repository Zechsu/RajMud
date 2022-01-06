#include <globals.h>

inherit "/std/obj/beetle";

void create() {
    ::create();
    set_short("titan");
    set_long("The largest beetle there is, humongous");
    set_ids(({"titan", "beetle", "titan beetle"}));
}