#include <globals.h>
#include "include/item.h"

inherit BASE;
inherit M_DESC;
inherit M_VISIBLE;
inherit LIB_PERSIST;

void create() {
    ::create();
    if (!sizeof(query_ids())) {
        set_ids(({}));
    }
}

int can_get(object who) {
    if (!who) {
        who = this_player();
    }
    return 1;
}

varargs mixed event_recieved(object who) {
    if (!who) {
        who = this_player();
    }
    return 0;
}

protected mixed* add_save(mixed* vars) {
    if (!vars) vars = ({});
    return persist::add_save(vars);
}

string* query_save() {
    return persist::query_csaved();
}

varargs mixed event_get(object who) {
    if (!who) {
        who = TP;
    }
    if (!can_get(who)) {
        return notify_fail("You can't get that.\n");
    }
    write("You get the " + query_short() + ".\n");
    say(who->query_name() + " gets the " + query_short() + "\n");
    ::move(who);
    event_recieved(who);
    return 1;
}

void event_drop(mixed dest) {
    write("You drop the " + query_short() + ".\n");
    say(TP->query_name() + " drops " + query_short() + "\n");
    ::move(dest);
}

int is_item() {
    return 1;
}
