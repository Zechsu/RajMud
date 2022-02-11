#include <lib.h>
#include <modules.h>

inherit LIB_CONTAINER;
inherit M_DECAY;

void create() {
    ::create();
    set_short("corpse");
    set_long("The corpse of someone.");
    set_ids(({"corpse"}));
    add_save(({"short_desc", "long_desc", "ids", "adjectives"}));
}

string query_long() {
    string ret = ::query_long();
    object* inv = all_inventory(this_object());
    int size = sizeof(inv);

    if (size) {
        ret += "\nIt contains: \n";
        for (int i = 0; i < size; i++) {
            ret += "  " + inv[i]->query_short();
            if (i+1 != size) {
                ret += "\n";
            }
        }
    }
    return ret;
}