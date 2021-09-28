#include <command.h>

string help();

int main(string str) {
    object tp = this_player();
    object ob;

    if (!str) {
        tell_object(tp, help());
        return 1;
    }

    if (stat(tp->query_cwd() + str + ".c") != ({})) {
        ob = new(tp->query_cwd() + str);
        ob->move(environment(tp));
        tell_object(tp, "Cloned " + str + ".\n");
        return 1;       
    }
    else {
        tell_object(tp, "Object not found.\n");
        return 1;
    }
}

string help() {
    return "Usage: clone <item name in directory>";
}