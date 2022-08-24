#include <command.h>

int main(string arg) {
    object* users = users();
    string broadcaster = map(lower_case(this_player()->query_name()), (: $1-32 :));
    if (!arg || trim(arg) == "") {
        return notify_fail("Broadcast what?\n");
    }
    foreach (object usr in users) {
        tell_object(usr, "\n    %^RED%^-~<= MESSAGE FROM " + broadcaster +" =>~-%^RESET%^\n\n");
        tell_object(usr, "%^BOLD%^%^YELLOW%^    " + arg + "%^RESET%^\n");
    }
    return 1;
}