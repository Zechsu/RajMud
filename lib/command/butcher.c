#include <command.h>

int main(string arg) {
    object ob;
    if (!arg || trim(arg) == "") {
        return notify_fail("Butcher what?\n");
    }
    ob = present(arg, this_player());
    if (!ob) ob = present(arg, environment(this_player()));
    if (!ob) return notify_fail("Couldn't find that.\n");
    if (!ob->is_butcherable()) return notify_fail("You can't butcher that!\n");
    return ob->event_butcher(this_player());
}