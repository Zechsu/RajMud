#include <command.h>

int main(string str) {
    object tp = this_player();
    object* inv = all_inventory(tp);
    inv = sort_array(inv, (:strcmp($1->query_short(), $2->query_short()):));

    if (!str || !sizeof(trim(str))) {
        tell_object(tp, "You currently hold: \n");
        foreach(object ob in all_inventory(tp)) {
            string ret = ob->query_short();
            if (ob->query_wielded()) {
                ret += " (wielded)\n";
                write(ret);
                continue;
            }
            write(ret + "\n");
        }
        return 1;
    } else {
        return 1;
    }
}