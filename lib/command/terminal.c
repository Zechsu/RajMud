#include <command.h>

string help();

int main(string str) {
    if (!str) {
        return notify_fail(help());
    }

    if (str == "color" || str == "colour") {
        this_player()->set_color(1);
        return 1;
    }
    else if (str == "none") {
        this_player()->set_color(0);
        return 1;
    }
    return notify_fail(help());
}

string help() {
    return "Usage:\nterminal <color> or\nterminal <none>\n";
}