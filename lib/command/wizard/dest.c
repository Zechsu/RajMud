#include <command.h>

int main(string arg)
{
    object tp = this_player();
    object* inv = all_inventory(environment(tp));

    if (!arg) {
        return notify_fail("usage: dest object\n");
    }

    inv = filter_array(inv, (: !living($1) :));
    inv = filter_array(inv, (: !$1->is_prop() :));

    foreach(object ob in inv) {
        if (member_array(arg, ob->query_ids()) != -1) {
            ob->remove();
            write("Destroyed " + arg + "\n");
            return 1;
        }
    }

    return notify_fail("Object not found.\n");
}
