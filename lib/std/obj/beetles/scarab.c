#include <globals.h>

inherit "/std/obj/beetle";

void create() {
    ::create();
    set_short("scarab");
    set_long("Ancient creature, symbol of the Egyptian god of the sun Ra");
    set_ids(({"scarab", "beetle", "scarab beetle"}));
}