#include <command.h>

int main(string arg) {
    string item, limb;
    if (!arg || trim(arg) == "") {
        return notify_fail("Wield what?\n");
    }

    if (sscanf(arg, "%s in %s", item, limb) == 2) {
        object ob = present(item, this_player());
        if (!ob) ob = present(item, environment(this_player()));
        if (ob->is_weapon()) {
            return ob->event_wield(this_player(), limb);
        }
    }
    else {
        object ob = present(arg, this_player());
        if (!ob) ob = present(arg, environment(this_player()));
        if (ob->is_weapon()) {
            return ob->event_wield(this_player(), 0);
        }
    }
    return notify_fail(sprintf("Invalid wield\nWEP:%s\nLIMB:%s\n", item, limb));
}