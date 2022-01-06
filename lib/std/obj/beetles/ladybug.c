#include <globals.h>

inherit "/std/obj/beetle";

void create() {
    ::create();
    set_short(alternate_colors("ladybug", ({"%^RED%^", "%^YELLOW%^"})));
    set_long("Red or yellow, black dotted, and very delicate lady");
    set_ids(({"ladybug"}));
}

varargs string query_short(int flag) {
    return ::query_short(1);
}