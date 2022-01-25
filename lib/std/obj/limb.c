#include <lib.h>
#include <modules.h>

inherit LIB_ITEM;
inherit M_DECAY;

private string* butcher_materials = ({});

void create() {
    ::create();
    set_short("severed limb");
    set_long("Remains of a limb");
    set_ids(({"limb"}));
    butcher_materials = ({"human meat"});
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

void set_butcher(string* mats) {
    butcher_materials = mats;
}

int is_butcherable() {
    return 1;
}

mixed event_butcher(object who) {
    foreach (string mat in butcher_materials) {
        object ob = new(LIB_RESOURCE);
        ob->set_short(mat);
        ob->set_ids(({mat}));
        ob->set_long(mat);
        ob->set_resource(mat);
        ob->add_weight(15);
        ob->event_get(who);
    }
    this_object()->remove();
    return 1;
}