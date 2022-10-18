#include <lib.h>

inherit LIB_ITEM;

string dispense_info();
int do_dispense(string arg);

void create() {
    ::create();
    // string* grad = color_gradient(({247, 240, 166}), ({207, 247, 166}), 8); string* grad2 = color_gradient(({207, 247, 166}),
    // ({247, 240, 166}), 8); return apply_gradient("item dispenser", grad+grad2);
    set_short(alternate_colors("item dispenser", ({"%^GREEN%^", "%^YELLOW%^"}), 2));
    set_ids(({"item dispenser", "dispenser"}));

    add_object("/domains/test/items/watch");
    add_object("/domains/test/items/sshapkata");
    add_object("/domains/test/weps/shortsword");
    add_object("/std/obj/tools/axe");
    add_object("/realm/edmond/wbox");
    add_object("/realm/edmond/compass");

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
            list + ".";
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