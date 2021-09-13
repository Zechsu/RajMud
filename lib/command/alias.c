#include <command.h>

string help();

int main(string arg) {
    string action, alias, command;

    if (!arg) {
        write(help());
        return 1;
    }
    if (arg == "list") {
        write(dump_variable(this_player()->query_aliases()));
        return 1;
    }

    if (sscanf(arg, "%s %s %s", action, alias, command) == 3) {
        if (action == "add") {
            if (this_player()->add_alias(alias, command)) {
                write("Bound " + alias + " to " + command + ".\n");
            }
            else {
                write("Couldn't add alias.\n");
            }
        }
        return 1;
    }
    else if (sscanf(arg, "%s %s", action, alias) == 2) {
        if (action == "remove") {
            if (this_player()->remove_alias(alias)) {
                write("Removed alias " + alias + "\n");
            } else {
                write("No such alias.\n");
            }
        }
        return 1;
    }

    return 1;
}

string help() {
    return "Usage: alias <add/remove/list>\n";
}