#include <globals.h>

inherit LIB_ITEM;
inherit M_INVENTORY;

void create() {
    item::create();
    m_inventory::create();
}

int is_container() {
    return 1;
}

string query_contents() {
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