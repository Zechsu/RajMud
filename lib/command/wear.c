#include <command.h>

int main(string arg) {
    string item, limb;
    if (!arg || trim(arg) == "") {
        return notify_fail("Wear what?\n");
    }

    if (sscanf(arg, "%s in %s", item, limb) == 2) {
        object ob = present(item, this_player());
        if (!ob) ob = present(item, environment(this_player()));
        if (!ob) return notify_fail(sprintf("Couldn't find %s.\n", arg));
        if (ob->is_wearable()) {
            return ob->event_wear(this_player(), limb);
        }
    }
    else {
        object ob = present(arg, this_player());
        if (!ob) ob = present(arg, environment(this_player()));
        if (!ob) return notify_fail(sprintf("Couldn't find %s.\n", arg));
        if (ob->is_wearable()) {
            return ob->event_wear(this_player());
        }
    }
    return 0;
}