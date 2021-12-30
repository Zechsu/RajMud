#include <command.h>

string help();

int main(string str) {
    object tp = this_player();
    object ob;

    if (!str || !sizeof(trim(str))) {
        tell_object(tp, help());
        return 1;
    }

    if (strsrch(str, "the") != -1) {
        str = replace_string(str, "the ", "");
    }

    if (ob = present(str, tp)) {
        ob->event_drop(environment(tp));
        return 1;
    }

    return notify_fail("You're not holding that.\n");
}

string help() {
    return "Usage: drop <item>\n";
}