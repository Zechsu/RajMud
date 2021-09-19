#include <globals.h>
#include <command.h>

int spawn_item(object tp, string item, string domain);
string help();

int main(string str) {
    object tp = this_player();
    string item, domain;

    if (!str || trim(str) == "") {
        tell_object(tp, help());
        return 1;
    }

    if (sscanf(str, "item %s %s", item, domain) == 2) {
        return spawn_item(tp, item, domain);
    }
    return 1;
}

int spawn_item(object tp, string item, string domain) {
    object ob;
    string dir = sprintf("/domains/%s/items/%s.c", domain, item);
    if (get_dir(dir)) {
        ob = new(dir);
        ob->move(environment(tp));
        tell_object(tp, "Spawned " + item + "\n");
        return 1;
    } else{
        tell_object(tp, "Invalid domain\n");
        return 1;
    }
    return 0;
}

string help() {
    return "Usage: spawn item <item name> <domain>\n";
}