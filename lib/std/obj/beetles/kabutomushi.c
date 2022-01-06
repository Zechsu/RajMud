#include <globals.h>

inherit "/std/obj/beetle";

void create() {
    ::create(); 
    set_short("%#5f0a0a%#kabutomushi%^RESET%^");
    set_long("The japanese brother of the rhinoceros.");
    set_ids(({"beetle", "kabuto", "mushi", "kabutomushi"}));
}
