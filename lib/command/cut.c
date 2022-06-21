#include <command.h>

int main(string arg) {
    object gath;
    if (!arg || trim(arg) == "") {
        return notify_fail("Cut what?\n");
    }
    gath = present(arg, ENV(TP));
    if (!gath) {
        return notify_fail("Couldn't find that here.\n");
    } 
    if (gath->query_action() != "cut") {
        return notify_fail("You can't cut that.\n");
    }
    else {
        return gath->event_gather(this_player());
    }
}