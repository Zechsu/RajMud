#include <lib.h>
#include <modules.h>

inherit LIB_ITEM;
inherit M_DECAY;

private string race;
private string* butcher_materials = ({});
private string* organs = ({});

void set_race(string r);
protected void setup_limb();
void set_butcher(string* mats);

void create(string race) {
    ::create();
    set_race(race);
    // default decay time for cloned objects is 50 seconds
    if (clonep()) {
        set_decay(5);
    }
    setup_limb();
}

protected void setup_limb() {
    set_short("severed " + race + " limb");
    set_long("Remains of a " + race + " limb.");
    set_ids(({"limb"}));
    set_butcher(({"meat"}));
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

void set_race(string r) {
    race = r;
}

string query_race() {
    return race;
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
        ob->set_long("It's " + capitalize(mat));
        ob->set_resource(mat);
        ob->set_adjectives(({race}));
        ob->add_weight(15);
        ob->event_get(who);
    }
    this_object()->remove();
    return 1;
}