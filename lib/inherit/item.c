#include <globals.h>

inherit M_DESC;

private nosave string* ids;
private mapping messages;

void create() {
    if (!sizeof(ids)) {
        ids = ({});
    }
    if (!sizeof(messages)) {
        messages = ([]);
    }
}

 int set_ids(string* new_ids) {
     ids = new_ids;
     return 1;
 }

string* query_ids() {
    return ids;
}

int id(string id) {
    if (member_array(id, ids) != -1) {
        return 1;
    }
    else {
        return 0;
    }
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

void move(mixed dest) {
    move_object(dest);
}

void remove()
{
    destruct(this_object());
}

int event_get(object player, int amount) {
    if (!player) {
        player = this_player();
    }
    if (!amount)
    {
        amount = 1;
    }

    move(player);
    player->add_item_to_inventory(this_object(), amount);
    return 1;
}

int event_drop(object player) {
    if (!player) {
        player = this_player();
    }

    move(environment(player));
    player->remove_item_from_inventory(this_object());
    return 1;
}

int can_get() {
    return 1;
}