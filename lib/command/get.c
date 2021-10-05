#include <command.h>

string help();
int get(object tp, mixed item);

int main(string str) {
    object tp = this_player();
    object room = environment(tp);
    object* inv = room->query_items();

    if (!str || !sizeof(trim(str))) {
        tell_object(tp, help());
        return 1;
    }

    if (strsrch(str, "the") != -1) {
        str = replace_string(str, "the ", "");
    }

    foreach(object ob in inv) {
        if (member_array(str, ob->query_ids()) != -1) {
            if (ob->can_get()) {
                ob->event_get(tp);
                write("You pick up the " + ob->query_short() + ".\n");
                say(tp->query_name() + " picks up " + ob->query_short() + "\n");
                return 1;
            }
            else {
                return notify_fail("You can't get that.\n");
            }
        }
    }

    return notify_fail("Couldn't find that here.\n");
}

string help() {
    return "Usage: get <item>\n";
}