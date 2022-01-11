#include <command.h>

string help() {
    return "Usage: tp <player1> <player2>\nIf no player2, you'll be teleported to player1\n";
}

int main(string str) {
    string pl1, pl2;
    if (!str) {
        return notify_fail(help());
    }
    if (sscanf(str, "%s %s", pl1, pl2) == 2) {
        object player1, player2;

        if (pl2 == "me")
            player2 = this_player();
        else
            player2 = find_player(pl2);

        player1 = find_player(pl1);

        if (player1 && player2) {
            string where = file_name(environment(player2));
            player1->event_move(where);
            if (pl2 == "me") {
                write("You teleport " + player1->query_short() + " to you.\n");
                tell_object(player1, "You materialize before " + player2->query_short() + ".\n");
                player1->force_me("look");
            }
            else {
                write("You teleport " + pl1 + " to " + pl2 + ".\n");
                player1->force_me("look");
                say(pl1, sprintf("%s materializes before you.\n", pl1->query_short()));
            }
            return 1;
        }
    }
    if (sscanf(str, "%s", pl1) == 1) {
        object target = find_player(pl1);
        if (target) {
            object tp = this_player();
            string where = file_name(environment(target));
            tp->event_move(where);
            write("You teleport to " + pl1 + ".\n");
            say(sprintf("%s materializes before you.\n", tp->query_short()));
            tp->force_me("look");
            return 1;
        }
    }

    return notify_fail(help());
}