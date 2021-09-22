#include <command.h>

string help();
int drop(object tp, mixed item);

int main(string str) {
    object tp = this_player();
    object* inv = all_inventory(tp);

    if (!str || !sizeof(trim(str))) {
        tell_object(tp, help());
        return 1;
    }

    if (strsrch(str, "the") != -1) {
        str = replace_string(str, "the ", "");
    }

    foreach(object ob in inv) {
        if (member_array(str, ob->query_ids()) != -1) {
            ob->move(environment(tp));
            tell_object(tp, "You drop " + ob->query_short() + "\n");
            say(tp->query_name() + " drops " + ob->query_short() + "\n");
            return 1;
        }
        else {
            tell_object(tp, "You're not holding that.\n");
            return 1;
        }
    }

    tell_object(tp, help());
    return 1;
}

string help() {
    return "Usage: drop <item>\n";
}