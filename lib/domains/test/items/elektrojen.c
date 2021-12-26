#include <globals.h>
#include "colors.h"

inherit LIB_ITEM;

void create() {
    ::create();
    set_short("elektrojen");
    set_long("elektorjen bro");
    set_ids(({"elektrojen"}));
}

int do_use(string arg) {
    if (!arg) {
        return 0;
    }
    else if (lower_case(arg) == "elektrojen") {
        write(ELECTRIC + "Tzzzt%^RESET%^\n");
        return 1;
    }
    return 0;
}

void init() {
    add_action("do_use", "use");
}