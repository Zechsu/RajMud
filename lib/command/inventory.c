#include <command.h>

int main(string str) {
    object tp = this_player();
    object* inv = all_inventory(tp);
    inv = sort_array(inv, (:strcmp($1->query_short(), $2->query_short()):));
    inv = filter_array(inv, (: !$1->query_worn() :));

    if (!str || !sizeof(trim(str))) {
        tell_object(tp, "You are currently holding ");
        write(list_strings(inv->query_short()));
        // foreach(object ob in inv) {
        //     string ret = ob->query_short();
        //     write(ret);
        //     // string attr = ob->worn_attributes();
        //     // write(sprintf("  %-30s %-30s\n", ret, attr? attr : ""));
        // }

        write("\n");
        return 1;
    }

    return 1;
}