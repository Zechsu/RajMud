#include <command.h>

int main(string arg) {
    object tp = this_player();
    object* eqs = all_inventory(tp);
    eqs = filter_array(eqs, (: $1->query_worn() :));
    if (sizeof(eqs) == 0) {
        tell_object(tp, "You're not equipped with anything.\n");
        return 1;
    }
    foreach (object item in eqs) {
        tell_object(tp, sprintf("%-35s %%^GREEN%%^(%-s)%%^RESET%%^\n", item->query_short(), list_strings(item->query_worn())));
    }
    return 1;
}