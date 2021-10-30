#include <globals.h>

private mapping search_table;

void set_search_table(mapping table) {
    search_table = table;
}

mixed event_searched(object who) {
    mixed result;
    if (!who) {
        who = this_player();
    }
    result = element_of_weighted(search_table);
    if (result != 0) {
        object ob = new(result);
        ob->move(this_player());
        return "You found " + ob->query_short() + "!\n";
    }
    return "You did not find anything interesting.\n";
}
