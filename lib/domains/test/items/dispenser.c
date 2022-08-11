#include <lib.h>

inherit LIB_ITEM;

string dispense_info();
int do_dispense(string arg);

void create() {
    ::create();
    set_short("%^MAGENTA%^item dispenser%^RESET%^");
    set_ids(({"item dispenser", "dispenser"}));

    add_object("/domains/test/items/watch");
    add_object("/domains/test/items/sshapkata");
    add_object("/std/obj/tools/axe");

    set_long(dispense_info());
}

void init() {
    add_action("do_dispense", "dispense");
}

string dispense_info() {
    object* inv = all_inventory(this_object());
    string list = list_strings(inv->query_short());
    return "Use dispense <item> to get something\n" +
            "List of items: " +
            list + ".\n";
}

int do_dispense(string arg) {
    string* ids;
    object selected;
    if (!arg || trim(arg) == "")
        return 0;

    ids = decompose(all_inventory(this_object())->query_ids());
    selected = present(arg, this_object());
    if (selected) {
        object ob = clone_object(base_name(selected));
        ob->move(environment(this_object()));
        tell_room(environment(this_object()), "The dispenser shoots out a " + ob->query_short() + "!\n");
        return 1;
    }
}