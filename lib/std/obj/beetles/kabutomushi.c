#include <globals.h>

inherit "/std/obj/beetle";

void create() {
    ::create(); 
    set_short("%#5f0a0a%#kabutomushi%^RESET%^");
    set_long("A lovely reddish dark brown male kabutomushi");
    set_ids(({"beetle", "kabuto", "mushi", "kabutomushi"}));
}
