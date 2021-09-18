#include <command.h>

int look(object tp);
int look_at(object tp, string look_at_item);
string help();

int main(string arg) {
    object tp = this_player();
    string look_at_item;

    if (!arg || !sizeof(trim(arg))) {
        return look(tp);
    }

    if (sscanf(arg, "at %s", look_at_item) == 1) {
        return look_at(tp, look_at_item);
    }

    return 1;
}

int look(object tp) {
    string desc;
    string exits = "";
    object room = environment(tp);
    string* exit_keys = keys(room->query_exits());

    if (sizeof(exit_keys) == 1) {
        exits = exit_keys[0] + " ";
    }
    else {
        foreach (string exit in exit_keys) {
            exits = exits + exit + " ";
        }
    }

    desc = sprintf("%c["+(33)+"m", 27) + room->query_short() + sprintf("%c["+(0)+"m", 27) + " [ " + exits + "]\n\n" + room->query_long() + "\n";
    tell_object(tp, desc);

    foreach(object ob in all_inventory(room)) {
        if (interactive(ob) && tp != ob) {
            tell_object(tp, ob->query_name() + " stands here.\n");
            continue;
        }
        if (inherits(LIB_ITEM, ob)) {
            tell_object(tp, ob->query_short() + " is on the ground.\n");
        }
    }
    return 1;
}

int look_at(object tp, string look_at_item) {
    object room = environment(tp);

    foreach (object ob in all_inventory(room)) {
        if (inherits(LIB_ITEM, ob) && ob->id(look_at_item)) {
            tell_object(tp, ob->query_long() + "\n");
            return 1;
        }
    }
    return 0;
}

string help() {
    return "Usage: look\n";
}