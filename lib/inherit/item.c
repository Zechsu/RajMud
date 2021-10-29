#include <globals.h>
#include "include/item.h"

inherit BASE;
inherit M_DESC;
inherit LIB_PERSIST;

private mapping messages;

void create() {
    if (!sizeof(ids)) {
        ids = ({});
    }
    if (!sizeof(messages)) {
        messages = ([]);
    }
}

string* query_ids() {
    return ids;
}

int set_message(string kind, string mess) {
    mess = replace_string(mess, "$N", query_short());
    messages[kind] = mess;
}

string query_message(string kind) {
    if (messages[kind]) {
        return messages[kind];
    }
    else {
        return sprintf("a %s is on the ground.", query_short());
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

void move(mixed dest) {
   ::move(dest);
}
