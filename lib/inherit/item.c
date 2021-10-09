#include <globals.h>
#include "include/item.h"

inherit BASE;
inherit M_DESC;

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

int event_get(object who, int amount) {
    if (!who) {
        who = this_player();
    }
    if (!amount)
    {
        amount = 1;
    }

    if (can_get()) {
        move(who);
        who->add_item_to_inventory(this_object(), amount);
        return 1;
    }
    return 0;
}

int event_drop(object player) {
    if (!player) {
        player = this_player();
    }

    move(environment(player));
    player->remove_item_from_inventory(this_object());
    return 1;
}

int event_put(object who, object where) {
    who->remove_item_from_inventory(this_object());
    move(where);
    where->add_item_to_inventory(this_object());
    return 1;
}

int can_get() {
    return 1;
}