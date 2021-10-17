#include <command.h>

string help();
int get(object tp, string item);
int get_from(object tp, string item, string from);

int main(string str) {
    object tp = this_player();
    object ob;
    string item, cont;

    if (!str || !sizeof(trim(str))) {
        tell_object(tp, help());
        return 1;
    }

    if (strsrch(str, "the") != -1) {
        str = replace_string(str, "the ", "");
    }

    if (sscanf(str, "%s from %s", item, cont) == 2) {
	    return 1;
        return get_from(tp, item, cont);
    }
    else if (sscanf(str, "%s %s", item, cont) == 2) {
        return get_from(tp, item, cont);
    }
    else {
        return get(tp, str);
    }

    return notify_fail("Couldn't find that here.\n");
}

int get(object tp, string item) {
    object room = environment(tp);
    object ob;
    if (ob = present(item, room)) {
        if (ob->event_get()) {
            write("You pick up the " + ob->query_short() + ".\n");
            say(tp->query_name() + " picks up " + ob->query_short() + "\n");
            return 1;
        }
        else {
            return notify_fail("You can't get that.\n");
        }
    }

    return notify_fail("Couldn't find that here.\n");
}

// TODO: please
int get_from(object tp, string item, string from) {
    object cont, ob;
    if (cont = present(from)) {
        if (cont->is_container()) {
            if (ob = present(item, cont)) {
                if (ob->event_get(tp)) {
                    write("You get " + ob->query_short() + " from " + cont->query_short() + ".\n");
                    cont->remove_item_from_inventory(ob);
                    return 1;
                }
                else {
                    return notify_fail("You can't get that.\n");
                }
            }
            else {
                return notify_fail("Couldn't find that inside.\n");
            }
        }
        else {
            return notify_fail("Not a container.\n");
        }
    }
    else {
        return notify_fail("Couldn't find that.\n");
    }
}

string help() {
    return "Usage: get <item>\nget <item> from <container>\n";
}
