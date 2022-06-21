#include <command.h>

int main(string arg) {
    object gath;
    if (!arg || trim(arg) == "") {
        return notify_fail("Mine what?\n");
    }
    gath = present(arg, ENV(TP));
    if (!gath) {
        return notify_fail("Couldn't find that here.\n");
    } 
    if (gath->query_action() != "mine") {
        return notify_fail("You can't mine that.\n");
    }
    else {
        return gath->event_gather();
    }
}