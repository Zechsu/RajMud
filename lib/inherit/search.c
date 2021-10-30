#include <globals.h>

private mapping table = ([]);

void create() {

}

mapping query_search_table() {
    return table;
}

void set_search_table(mapping new_table) {
    table = new_table;
}

int can_search(object who) {
    return 1;
}

mixed do_search(object who) {
    mixed res = element_of_weighted(table);
    if (!can_search()) {
        return "You can't do that.\n";
    }
    if (objectp(res)) {
        return res;
    }
    else {
        return "You did not find anything interesting.\n";
    }
}