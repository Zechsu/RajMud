#include <globals.h>
#include <command.h>

int spawn_item(object tp, string item, string domain);
int spawn_mobile(object tp, string mobile, string domain);
string help();

int main(string str) {
    object tp = this_player();
    string item, domain;

    if (!str || trim(str) == "") {
        tell_object(tp, help());
        return 1;
    }

    if (sscanf(str, "item %s %s", domain, item) == 2) {
        return spawn_item(tp, item, domain);
    }
    if (sscanf(str, "mobile %s %s", domain, item) == 2) {
        return spawn_mobile(tp, item, domain);
    }
    if (sscanf(str, "item %s", domain) == 1) {
        return notify_fail("Enter a domain.\n");
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

int spawn_mobile(object tp, string mobile, string domain) {
    object ob;
    string dir = sprintf("/domains/%s/mobiles/%s.c", domain, mobile);
    if (get_dir(dir)) {
        ob = new(dir);
        ob->move(environment(tp));
        write("Spawned " + mobile + "\n");
        return 1;
    } else {
        return notify_fail("Invalid domain.\n");
    }
    return 0;
}

string help() {
    return "Usage: spawn item <domain> <name>\n  spawn mobile <domain> <name>\n";
}
