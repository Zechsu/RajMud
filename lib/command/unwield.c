#include <command.h>

int main(string arg) {
    object ob;
    if (!arg || trim(arg) == "") {
        return notify_fail("Unwield what?\n");
    }
    ob = present(arg, this_player());
    if (ob) {
        if (!ob->is_wieldable()) {
            return notify_fail(sprintf("%s is not wieldable.\n", arg));
        }
        return ob->event_remove();
    }
    else {
        return notify_fail("You do not have that.\n");
    }
}