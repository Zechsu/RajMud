#include <globals.h>

inherit LIB_ITEM;

void create() {
    ::create();
    set_short("30cm bbc dildo");
    set_long("It appears to be the smallest size Kocinofs collection has to offer.");
    set_ids(({"dildo", "bbc", "bbc dildo", "30cm bbc dildo"}));
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
