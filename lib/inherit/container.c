#include <globals.h>

inherit LIB_ITEM;
inherit M_INVENTORY;

void create() {
    item::create();
    m_inventory::create();
    set_save_recurse(1);
}

int is_container() {
    return 1;
}

string query_contents_mess() {
    string ret = "";
    object* inv = all_inventory(this_object());
    int size = sizeof(inv);

    if (!size) {
        ret = "It's empty";
    }
    else {
        ret = "It holds: \n";
        for (int i = 0; i < size; i++) {
            ret += inv[i]->query_short();
            if (i+1 != size) {
                ret += "\n";
            }
        }
    }
    return ret;
}

int can_put(object who) {
    if (!who) {
        who = this_player();
    }
    return 1;
}

mixed event_recieve_item(object item, object who) {
    if (!who) {
        who = this_player();
    }
    if (!item) {
        debug_message("NO ITEM ON EVENT_RECIEVE_ITEM\n");
        return 0;
    }
    if (!can_put(who)) {
        return "You can't do that!\n";
    }
    if (is_full()) {
        return "It's full!\n";
    }
    item->move(this_object());
    return 1;
}