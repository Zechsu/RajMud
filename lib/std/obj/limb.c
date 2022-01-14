#include <lib.h>
#include <modules.h>

inherit LIB_ITEM;
inherit M_DECAY;

void create() {
    ::create();
    set_short("severed limb");
    set_long("Remains of a limb");
    set_ids(({"limb"}));
    // default decay time for cloned objects is 50 seconds
    if (clonep()) {
        set_decay(5);
    }
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