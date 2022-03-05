#include <command.h>

int main(string arg) {
    object ob;
    if (!arg) {
        return notify_fail("Source on what?\n");
    }
    if (lower_case(arg) == "here") {
        string file = ENV(TP) + ".c";
        write(read_file(file) + "\n");
        return 1;
    }
    if (arg[<2..] != ".c") {
        arg += ".c";
    }
    if (get_dir(arg)) {
        write(read_file(arg) + "\n");
        return 1;
    }
    ob = present(arg, this_player());
    if (!ob) ob = present(arg, environment(this_player()));
    write(read_file(base_name(ob)) + "\n");
    return 1;
}
