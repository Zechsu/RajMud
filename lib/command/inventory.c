#include <command.h>

int main(string str) {
    object tp = this_player();

    if (!str || !sizeof(trim(str))) {
        tell_object(tp, "You currently hold: \n");
        foreach(object ob in all_inventory(tp)) {
            write(ob->query_short() + "\n");
        }
        return 1;
    } else {
        return 1;
    }
}