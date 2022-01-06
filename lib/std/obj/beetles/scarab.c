#include <globals.h>
#include <colors.h>

inherit "/std/obj/beetle";

void create() {
    ::create();
    set_short("%#FFD700%#scarab%^RESET%^");
    set_long("Ancient creature, symbol of the Egyptian god of the sun Ra");
    set_ids(({"scarab", "beetle", "scarab beetle"}));
}