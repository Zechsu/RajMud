#include <command.h>

int main(string arg) {
    string item, limb;
    object ob;
    if (!arg || trim(arg) == "") {
        return notify_fail("Remove what?\n");
    }
    ob = present(arg, this_player());
    if (!ob) return notify_fail(sprintf("You do not have %s.\n", arg));
    if (ob->is_wearable()) {
        return ob->event_remove();
    }
    return 0;
}