#include <globals.h>

inherit LIB_ITEM;

void create() {
    ::create();
    set_short("lockpick");
    set_long("Use this to pick locks on doors.\n");
    set_ids(({"lockpick"}));
}

void init() {
    add_action("do_pick", "pick");
}

int do_pick(string str) {
    object tp = this_player();
    mixed res;
    object ob;
    if (!str) {
        return notify_fail("Pick what?\n");
    }
    if (!ENV(tp)->is_door(str)) {
        res = "Invalid target.\n";
    }
    if (ob = present(str)) {
        res = ob->event_pick_lock();
        write("You pick the lock.\n");
    }
    if (stringp(res)) {
        return notify_fail(res);
    }
    if (secure_random(11) == 1) {
        write("Your lockpicks breaks!\n");
        destruct(this_object());
        return 1;
    }

    return 1;
}