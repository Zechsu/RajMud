#include <globals.h>

inherit LIB_ITEM;

void create() {
    ::create();
    set_short("%#e8e8e8%#stone%^RESET%^");
    set_long("It's pretty round. Give it a rub.");
    set_ids(({"stone"}));
    set_message("on_ground", "a $N is on the ground.");
}

void init() {
    add_action("do_rub", "rub");
}

int do_rub(string str) {
    object tp = this_player();

    if (str == "stone" || str == "the stone") {
        if (tp->query_trait("skin_color") == "black") {
            tell_object(tp, "Go away!\n");
        } else {
            tell_object(tp, "Hello, good sir. Beautiful morning, ay?\n");
        }
        return 1;
    }
    else {
        return 0;
    }
}
