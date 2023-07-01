#include <lib.h>
#define GOBLIN_CAVE "/domains/goblincave/weps/"
#define ITEMS ({GOBLIN_CAVE + "sword", GOBLIN_CAVE + "slingshot", GOBLIN_CAVE + "club", GOBLIN_CAVE+"spear"})

inherit LIB_ITEM;

void create() {
    ::create();
    set_short("weapon box");
    set_long("Try your luck by opening it.");
    set_ids(({"weapon box", "box", "weapon"}));
}

void init() {
    add_action("do_open", "open");
}

int do_open(string arg) {
    mixed weapon;
    object ob;
    if (!arg || trim(arg) == "") {
        return 0;
    }
    if (ob = present(arg, this_player())) {
        weapon = new(element_of(ITEMS));
        if (weapon) {
            weapon->move(this_player());
            tell_object(this_player(), "You get " + weapon->query_short() + " from the box!\n");
            destruct(this_object());
            return 1;
        }
    }
    return 0;
}