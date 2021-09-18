#include <command.h>

string help();
int add_alias(object tp, string alias, string expanded);
int list_alias(object tp);
int remove_alias(object tp, string alias);

int main(string str) {
    string operation, arg;
    object tp = this_player();

    if (!str) {
        write(help());
        return 1;
    }
    if (str == "list") {
        return list_alias(tp);
    }
    
    if (sscanf(str, "%s %s", operation, arg) == 2) {
        switch (operation) {
            case "add": {
                string alias, expanded;
                if (sscanf(arg, "%s %s", alias, expanded) == 2) return add_alias(tp, alias, expanded);
                write(help());
                return 1;
            }
            case "remove": {
                return remove_alias(tp, arg);
            }
            default: {
                write(help());
                return 1;
            }
        }
    }

    return 1;
}

int add_alias(object tp, string alias, string expanded) {
    if (tp->add_alias(alias, expanded)) {
        tell_object(tp, "Bound alias " + alias + " to " + expanded + ".\n");
    }
    return 1;
}

int remove_alias(object tp, string alias) {
    if (tp->remove_alias(alias)) {
        tell_object(tp, "Removed alias " + alias + ".\n");
    }
    return 1;
}

int list_alias(object tp) {
    tell_object(tp, dump_variable(tp->query_aliases())+ "\n");
    return 1;
}

string help() {
    return "Usage: alias <add/remove/list>\n";
}
