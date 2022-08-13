#include <command.h>

int main(string str) {
    object tp = this_player();
    object* inv = all_inventory(tp);
    inv = sort_array(inv, (:strcmp($1->query_short(), $2->query_short()):));
    inv = filter_array(inv, (: !$1->query_worn() :));

    if (!str || !sizeof(trim(str))) {
        string* items = inv->query_short();
        if (sizeof(items)) {
            tell_object(tp, "You are currently holding ");
            tell_object(tp, list_strings(inv->query_short()));
        }
        else {
            tell_object(tp, "You are not holding anything.");
        }
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