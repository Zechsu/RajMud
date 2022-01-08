#include <globals.h>

inherit LIB_ITEM;

void create() {
    ::create();
    set_short("7m dildo");
    set_long("The biggerst dildo of Kocinoffs collection. Appart from using it himself Kocinoff uses this dildo to punish noughty students who bust a nut in the sublekalni. It can also be used as a weapon.");
    set_ids(({"dildo", "7m", "7m dildo"}));
}

void init() {
    add_action("do_swing", "swing");
}

int do_swing(string arg) {
    object tp = this_player();
    if (!arg || trim(arg) == "") {
        return 0;
    }
    if (member_array(arg, query_ids()) == -1) {
        return 0;
    }
    write("You swing your " + query_short() + " around.\n");
    say(sprintf("%s swing his %s around.\n", tp->query_short(), query_short()));
    return 1;
}