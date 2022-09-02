#include <command.h>
#include <globals.h>

string help();

int main(string str) {
    object tp = this_player();
    object ob;
    string file;

    if (!str) {
        tell_object(tp, help());
        return 1;
    }
    else if (str[0] != '/' && str[0] != '~' && str[0] != '^') {
        file = tp->query_cwd() + "/" + str;
    }
    else {
        file = tp->query_cwd() + str + ".c";
    }

    if (file[<2..] != ".c") {
        file += ".c";
    }

    if (stat(file) != ({})) {
        ob = new(file);
        if (ob->is_item() || ob->is_living()) {
            ob->move(environment(tp));
            write(sprintf("Cloned %s\n", ob->query_short()));
            return 1;   
        }
        else {
            destruct(ob);
            write("Cannot clone that.\n");
            return 1;
        }
    }
    else {
        tell_object(tp, "Object not found.\n");
        return 1;
    }
}

string help() {
    return "Usage: clone <item name in directory>\n";
}