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

    file = tp->query_cwd() + str + ".c";
    if (stat(file) != ({})) {
        ob = new(file);
        if (inherits(LIB_ITEM, ob)) {
            ob->move(environment(tp));
            tell_object(tp, "Cloned " + str + ".\n");
            return 1;   
        }
        else {
            destruct(ob);
            tell_object(tp, "Cannot clone that.\n");
            return 1;
        }
    }
    else {
        tell_object(tp, "Object not found.\n");
        return 1;
    }
}

string help() {
    return "Usage: clone <item name in directory>";
}