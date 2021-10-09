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

    desc = "%^YELLOW%^" + room->query_short() + "%^RESET%^" + exits + "\n\n" + room->query_long();
    write(desc + "\n");

    // ugly fix for not putting a random \n after the room long descriptions
    inv -= ({tp});
    inv = filter_array(inv, (: !$1->is_prop() :));
    if (sizeof(inv)) {
        tell_object(tp, "\n");
    }

    foreach(object ob in all_inventory(room)) {
        if (interactive(ob) && tp != ob) {
            tell_object(tp, ob->query_name() + " stands here.\n");
            continue;
        }
        if (inherits(LIB_ITEM, ob)) {
            write(ob->query_message("on_ground") + "\n");
        }
    }
    return 1;
}

int look_at(object tp, string look_at_item) {
    object room = environment(tp);
    object ob;

    if (strsrch(look_at_item, "the") != -1) {
        look_at_item = replace_string(look_at_item, "the ", "");
    }

    if (ob = present(look_at_item, tp)) {
        write(ob->query_long() + "\n");
        return 1;
    }
    if (ob = present(look_at_item, room)) {
        write(ob->query_long() + "\n");
        return 1;
    }

    // foreach (object ob in all_inventory(room)) {
    //     if (inherits(LIB_ITEM, ob) && member_array(look_at_item, ob->query_ids()) != -1) {
    //         write(ob->query_long() + "\n");
    //         return 1;
    //     }
    //     if (ob->is_prop()) {
    //         if (ob->id(look_at_item)) {
    //             tell_object(tp, ob->query_description() + "\n");
    //             return 1;
    //         }
    //     }
    // }

    return notify_fail("Couldn't find that.\n");
}

string help() {
    return "Usage: look\n";
}
