#include <command.h>

int main(string arg) {
    string desc;
    string exits = "";
    object room = environment(this_player());
    string* exit_keys = keys(room->query_exits());
    object* players;

    if (sizeof(exit_keys) == 1) {
        exits = exit_keys[0] + " ";
    }
    else {
        foreach (string exit in exit_keys) {
            exits = exits + exit + " ";
        }
    }

    desc = sprintf("%c["+(33)+"m", 27) + room->query_short() + sprintf("%c["+(0)+"m", 27) + " [ " + exits + "]\n\n" + room->query_long() + "\n";
    write(desc);

    foreach(object player in all_inventory(room)) {
        if (interactive(player) && this_player() != player) {
            write(player->query_name() + " stands here.\n");
        }
    }
    return 1;
}
