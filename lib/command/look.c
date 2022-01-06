#include <command.h>

int look(object tp);
int look_at(object tp, string look_at_item);
int look_in(object tp, string look_at_item);
string help();

int main(string arg) {
    object tp = this_player();
    string look_at_item;

    if (!arg || !sizeof(trim(arg))) {
        return look(tp);
    }

    if (arg == "here") {
        return look(tp);
    }

    if (sscanf(arg, "at %s", look_at_item) == 1) {
        return look_at(tp, look_at_item);
    }
    else if (sscanf(arg, "in %s", look_at_item) == 1) {
        return look_in(tp, look_at_item);
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
    string* exit_keys;
    object* inv;
    object* living;
    object* items;
    string ret = "";

    if (!room) {
        return notify_fail("You're in the void.\n");
    }

    exit_keys = room->query_exit_keys();
    inv = all_inventory(room);

    if (sizeof(exit_keys) == 0) {
        exits = "";
    } 
    else if (sizeof(exit_keys) == 1) {
        exits = " [ " + exit_keys[0] + " ] ";
    }
    else {
        exits = " [ " + implode(exit_keys, " | ") + " ] ";
    }

    desc = "%^YELLOW%^" + room->query_short() + "%^RESET%^" + exits + "\n" + room->query_long();
    write(desc + "\n");

    // ugly fix for not putting a random \n after the room long descriptions
    inv -= ({tp});
    inv = filter_array(inv, (: !$1->is_prop() :));

    living = filter_array(inv, (:$1->is_living():));
    items = filter_array(inv, (: $1->is_visible():));

    if (sizeof(items) || sizeof(living)) {
        tell_object(tp, "\n");
    }

    if (sizeof(living)) {
        foreach(object liv in living) {
            write(query_position_string(liv) + "\n");
        }
    }
    if (sizeof(items)) {
        int j;
        int sz = sizeof(items);
        ret = "You see ";
        if (sz == 1) {
            ret += items[0]->query_short();
        }
        else {
            for (j = 0; j < sz; j++) {
                string short = items[j]->query_short();
                if (!short) {
                    continue;
                }
                if (j == sz -1) {
                    ret += " and " + short;
                }
                else {
                    ret += short;
                }
                if (j < sz - 2) {
                    ret += ", ";
                }
            }
        }
        write(ret + "\n");
    }

    return 1;
}

int look_at(object tp, string look_at_item) {
    object ob;

    if (strsrch(look_at_item, "the") != -1) {
        look_at_item = replace_string(look_at_item, "the ", "");
    }

    if (strsrch(look_at_item, "here") != -1) {
        look_at_item = rtrim(replace_string(look_at_item, "here", ""));
        if (ob = present(look_at_item, ENV(tp))) {
            write(ob->query_long() + "\n");
            return 1;
        }
        else {
            return notify_fail("There is no " + look_at_item + " here.\n");
        }
    }
    ob = present(look_at_item, tp);
    if (!ob) ob = present(look_at_item, ENV(tp));
    if (ob) {
        write(ob->query_long() + "\n");
        return 1;
    }

    return notify_fail("Couldn't find that.\n");
}

int look_in(object tp, string look_at_item) {
    object ob;

    if (strsrch(look_at_item, "here") != -1) {
        look_at_item = rtrim(replace_string(look_at_item, "here", ""));
        if (ob = present(look_at_item, ENV(tp))) {
            if (ob->is_container()) {
                write(ob->query_contents_mess() + "\n");
                return 1;
            }
            else {
                return notify_fail("You can't look inside that.\n");
            }
        }
        else {
            return notify_fail("There is no " + look_at_item + " here.\n");
        }
    }
    
    ob = present(look_at_item, tp);
    if (!ob) ob = present(look_at_item, ENV(tp));
    if (ob) {
        if (ob->is_container()) {
            return ob->event_look_in(tp);
        }
        else {
            return notify_fail("You can't look inside that.\n");
        }
    }

    return notify_fail("Can't find that.\n");
}

string help() {
    return "Usage: look\n";
}
