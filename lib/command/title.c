#include <command.h>

int main(string arg) {
    if (!arg || trim(arg) == "") {
        return notify_fail("Enter a title.\n");
    }
    TP->set_title(arg);
    return 1;
}