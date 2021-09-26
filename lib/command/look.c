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
    else {
        return look_at(tp, arg);
    }

    return 1;
}

int look(object tp) {
    string desc;
    string exits = "";
    object room = environment(tp);
    string* exit_keys = keys(room->query_exits());
    object* inv = all_inventory(room);

    if (sizeof(exit_keys) == 0) {
        exits = "";
    } 
    else if (sizeof(exit_keys) == 1) {
        exits = " [ " + exit_keys[0] + " ] ";
    }
    else {
        exits = " [ " + implode(exit_keys, " | ") + " ] ";
    }

    desc = sprintf("%c["+(33)+"m", 27) + room->query_short() + sprintf("%c["+(0)+"m", 27) + exits + "\n\n" + room->query_long();
    tell_object(tp, desc + "\n");

    // ugly fix for not putting a random \n after the room long descriptions
    inv -= ({tp});
    inv = filter_array(inv, (: $1->is_prop() :));
    if (sizeof(inv)) {
        tell_object(tp, "\n");
    }

    foreach(object ob in all_inventory(room)) {
        if (interactive(ob) && tp != ob) {
            tell_object(tp, ob->query_name() + " stands here.\n");
            continue;
        }
        if (inherits(LIB_ITEM, ob)) {
            tell_object(tp, ob->query_message("on_ground") + "\n");
        }
    }
    return 1;
}

int look_at(object tp, string look_at_item) {
    object room = environment(tp);
    if (strsrch(look_at_item, "the") != -1) {
        look_at_item = replace_string(look_at_item, "the ", "");
    }

    foreach (object ob in all_inventory(room)) {
        if (inherits(LIB_ITEM, ob) && member_array(look_at_item, ob->query_ids()) != -1) {
            tell_object(tp, ob->query_long() + "\n");
            return 1;
        }
        if (ob->is_prop()) {
            if (ob->id(look_at_item)) {
                tell_object(tp, ob->query_description() + "\n");
                return 1;
            }
        }
    }

    tell_object(tp, "Couldn't find that here.\n");
    return 1;
}

string help() {
    return "Usage: look\n";
}
