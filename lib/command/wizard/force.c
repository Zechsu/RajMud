#include <command.h>

int main(string arg) {
    string target, cmd;
    if (!arg || trim(arg) == "") {
        return notify_fail("force <who> to <what>\n");
    }
    if (sscanf(arg, "%s to %s", target, cmd) == 2) {
        object ob = present(target, environment(this_player()));
        if (!ob) return notify_fail(target + " is not present.\n");
        if (!ob->is_living()) return notify_fail(target + " is not a living object.\n");
        return ob->force_me(cmd);
    } 
}