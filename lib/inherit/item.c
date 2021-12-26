#include <globals.h>
#include "include/item.h"

inherit BASE;
inherit M_DESC;
inherit M_VISIBLE;
inherit LIB_PERSIST;

private mapping messages;

void create() {
    ::create();
    if (!sizeof(query_ids())) {
        set_ids(({}));
    }
    if (!sizeof(messages)) {
        messages = ([]);
    }
}

string query_indefinite_article() {
    if (query_short()[0] == 'a') {
        return "an";
    }
    return "a";
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

void move(mixed dest) {
   ::move(dest);
}

int is_item() {
    return 1;
}
