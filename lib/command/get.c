#include <command.h>

string help();
int get(object tp, string item);
varargs int get_from(object tp, string item, string from, int all);

int main(string str) {
    object tp = this_player();
    string item, cont;

    if (!str || !sizeof(trim(str))) {
        tell_object(tp, help());
        return 1;
    }

    if (strsrch(str, "the") != -1) {
        str = replace_string(str, "the ", "");
    }
    if (sscanf(str, "%s all from %s", item, cont) == 2) {
        return get_from(tp, item, cont, 1);
    }
    if (sscanf(str, "%s from %s", item, cont) == 2) {
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
        return ob->event_get(tp);
    }

    return notify_fail("Couldn't find that here.\n");
}

varargs int get_from(object tp, string item, string from, int all) {
    object cont;
    cont = present(from, tp);
    if (!cont) cont = present(from, ENV(tp));

    if (!cont) {
        return notify_fail("Couldn't find " + from + " here.\n");
    }
    if (!cont->is_container()) {
        return notify_fail(cont->query_short() + " is not a container.\n");
    }
    if (all) {
        foreach (object i in all_inventory(cont)) {
            cont->event_get_from(tp, i->query_id());
            return 1;
        }
    }
    return cont->event_get_from(tp, item);
}

string help() {
    return "Syntax: get <item>\nget <item> from <container>\nget all from <container>\n";
}
