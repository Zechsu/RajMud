#include <command.h>

int main(string arg) {
    string item, limb;
    if (!arg || trim(arg) == "") {
        return notify_fail("Wield what?\n");
    }

    if (sscanf(arg, "%s in %s", item, limb) == 2) {
        object ob = present(item, this_player());
        if (!ob) return notify_fail(sprintf("You do not have %s.\n", arg));
        if (ob->is_wieldable()) {
            return ob->event_wear(this_player(), ({ limb }));
        }
        return notify_fail("You can't wield that.\n");
    }
    else {
        object ob = present(arg, this_player());
        if (!ob) return notify_fail(sprintf("You do not have %s.\n", arg));
        if (ob->is_wieldable()) {
            return ob->event_wear(this_player());
        }
        return notify_fail("You can't wield that.\n");
    }
    return 0;
}