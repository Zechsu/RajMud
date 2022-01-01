#include <command.h>

int main(string arg) {
    if (!arg) {
        return notify_fail("info on what?\n");
    }
    if (lower_case(arg) == "here") {
        string file = ENV(TP) + ".c";
        write(read_file(file) + "\n");
        return 1;
    }
}
