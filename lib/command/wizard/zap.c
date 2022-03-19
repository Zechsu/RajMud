#include <command.h>

int main(string arg) {
    object ob;
    if (!arg || trim(arg) == "") {
        return notify_fail("Zap who?\n");
    }

    ob = present(arg, environment(this_player()));
    if (ob) {
        if (!ob->is_living())
            return notify_fail("That is not a living being.\n");
        ob->event_die();
        write("Zapped " + arg + "\n");
        return 1;
    }
}