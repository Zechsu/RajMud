#include <command.h>

int main(string arg) {
    object ob;
    if (!arg || trim(arg) == "") {
        return notify_fail("Kill who?\n");
    }
    ob = present(arg, environment(this_player()));
    if (!ob) return notify_fail("Couldn't find " + arg + " here.\n");
    if (!ob->is_living()) return notify_fail(arg + " is not living.\n");
    if (ob == this_player()) return notify_fail("You can't kill yourself!\n");
    return this_player()->event_attack(ob);
}