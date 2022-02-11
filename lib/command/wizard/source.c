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
    ob = present(arg, this_player());
    if (!ob) ob = present(arg, environment(this_player()));
    write(read_file(base_name(ob) + ".c") + "\n");
    return 1;
}
