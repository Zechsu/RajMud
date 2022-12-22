#include <command.h>

int main(string arg) {
    object* users;
    string name;
    if (!arg || trim(arg) == "") {
        return notify_fail("Usage:\n    ooc <message>\n");
    }
    users = users();
    name = this_player()->query_name();
    foreach (object usr in users) {
        mapping info = ([]);
        tell_object(usr, sprintf("%%^BOLD%%^%%^CYAN%%^[OOC %s]%%^RESET%%^ %s\n", name, arg));
        info["from"] = name;
        info["message"] = arg;
        usr->send_gmcp_data("Game.OOC", json_encode(info));
    }
    return 1;
}

string help() {
    return "Usage:\n    ooc <message>\n";
}