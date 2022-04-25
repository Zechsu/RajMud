#include <command.h>

int look(object tp);
int look_at(object tp, string look_at_item);
int look_in(object tp, string look_at_item);
int look_at_on(object tp, string look_at_item, string target);
string help();

int main(string arg) {
    object tp = this_player();
    string look_at_item, target;

    if (!arg || !sizeof(trim(arg))) {
        return look(tp);
    }

    if (arg == "here") {
        return look(tp);
    }

    if (sscanf(arg, "at %s on %s", look_at_item, target) == 2) {
        return look_at_on(tp, look_at_item, target);
    }
    if (sscanf(arg, "%s on %s", look_at_item, target) == 2) {
        return look_at_on(tp, look_at_item, target);
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
    string desc, ret = "", exits = "";
    object room = environment(tp);
    string* exit_keys;
    object* inv, *living, *items, *specials;

    if (!room) {
        return notify_fail("You're in the void.\n");
    }

    exit_keys = room->query_exit_keys();
    inv = all_inventory(room);

    desc = "%^YELLOW%^" + room->query_short() + "%^RESET%^" + "\n" + room->query_long();
    tell_object(tp, desc + "\n");

    // ugly fix for not putting a random \n after the room long descriptions
    inv -= ({tp});
    // Remove prop objects
    inv = filter_array(inv, (: !$1->is_prop() :));
    // Remove invisible objects
    inv = filter_array(inv, (: $1->is_visible() :));

    living = filter_array(inv, (:$1->is_living():));
    items = filter_array(inv, (: $1->is_item() :));
    specials = filter_array(items, (: $1->is_portal() :));
    items -= specials;

    if (sizeof(exit_keys) == 1) {
        tell_object(tp, "  The only obvious exit is %^MAGENTA%^" + exit_keys[0] + ".%^RESET%^\n");
    }
    else {
        tell_object(tp, "  The only obvious exits are %^MAGENTA%^" + list_strings(exit_keys) + ".%^RESET%^\n");
    }
    if (sizeof(specials)) {
        int spsz = sizeof(specials);
        if (spsz == 1) {
            tell_object(tp, capitalize_colored(specials[0]->query_short()) + " is here.\n");
        }
        else {
            string sps = list_strings(specials->query_short()) + " are here.";
            write(capitalize_colored(sps) + "\n");
        }
    }

    if (sizeof(items) || sizeof(living)) {
        tell_object(tp, "\n");
    }

    if (sizeof(living)) {
        foreach(object liv in living) {
            write(query_position_string(liv) + "\n");
        }
    }
    if (sizeof(items)) {
        ret = "You see ";
        if (sizeof(items) == 1) {
            ret += items[0]->query_short();
        }
        else {
            ret += list_strings(map_array(items, (:$1->query_short():)));
        }
        write(ret + ".\n");
    }

    tp->gmcp("Room.Info");
    tp->gmcp("Room.Items");
    tp->gmcp("Room.Livings");
    return 1;
}

int look_at(object tp, string look_at_item) {
    object ob;

    if (strsrch(look_at_item, "the") != -1) {
        look_at_item = replace_string(look_at_item, "the ", "");
    }

    if (look_at_item == "me") {
        write(this_player()->query_long() + "\n");
        return 1;
    }

    if (strsrch(look_at_item, "here") != -1) {
        look_at_item = rtrim(replace_string(look_at_item, "here", ""));
        if (ob = present(look_at_item, environment(tp))) {
            write(ob->query_long() + "\n");
            return 1;
        }
        else {
            return notify_fail("There is no " + look_at_item + " here.\n");
        }
    }
    look_at_item = lower_case(look_at_item);
    ob = present(look_at_item, tp);
    if (!ob) ob = present(look_at_item, environment(tp));
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

int look_at_on(object tp, string look_at_item, string target) {
    object t, it;

    t = present(target, environment(tp));
    if (!t->is_living()) {
        return notify_fail("Invalid target.\n");
    }
    
    it = present(look_at_item, t);
    if (!it->query_worn()) {
        return notify_fail("Not wearing that.\n");
    }
    write(it->query_long() + "\n");
    return 1;
}

string help() {
    return "Usage: look\nlook at <object>\n";
}
