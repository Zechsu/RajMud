#include <command.h>

int main(string arg) {
    object tp = this_player();
    object* eqs = all_inventory(tp);
    int longest;
    if (!sizeof(tp->query_worn())) {
        return notify_fail("You're not equipped with anything.\n");
    }
    longest = sizeof(sort_array(tp->query_worn()->query_short(), (: sizeof($1) < sizeof($2) :))[0]);
    eqs = filter_array(eqs, (: $1->query_worn() :));
    if (sizeof(eqs) == 0) {
        tell_object(tp, "You're not equipped with anything.\n");
        return 1;
    }
    write(sprintf("  %-*s%s\n", longest+16, "ITEM", "WORN ON"));
    for (int i = 0; i < 80; i++) {
        write("=");
    }
    write("\n");
    foreach (object item in eqs) {
        tell_object(tp, sprintf("  %-*s %%^GREEN%%^(%-s)%%^RESET%%^\n", longest+15, item->query_short(), list_strings(item->query_worn())));
    }
    return 1;
}