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

varargs mixed event_look_in(object who) {
    if (!who) {
        who = TP;
    }
    write(query_contents_mess() + "\n");
    return 1;
}

int can_put(object who) {
    if (!who) {
        who = this_player();
    }
    if (is_inventory_full()) {
        return notify_fail("It is full.\n");
    }
    return 1;
}

varargs mixed event_recieve_item(object item, object who) {
    if (!who) {
        who = this_player();
    }
    if (!item) {
        debug_message("NO ITEM ON EVENT_RECIEVE_ITEM\n");
        return 0;
    }
    if (!can_put(who)) {
        return 0;
    }
    item->move(this_object());
    write("You put " + item->query_short() + " in " + query_short() + ".\n");
    say(sprintf("%s puts %s in %s", who->query_short(), item->query_short(), query_short()));
    return 1;
}

varargs mixed event_get(object who, string what) {
    object item;
    if (!who) {
        who = TP;
    }

    item = present(what, TO);
    if (!item) {
        return notify_fail("Couldn't find that inside " + query_short() + "\n");
    }
    return item->event_get_from(who, TO);
}