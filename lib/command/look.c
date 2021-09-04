#include <command.h>

int main(string arg) {
    string desc;
    object room = environment(this_player());
    desc = room->query_short() + "\n" + room->query_long() + "\n";
    write(desc);
    return 1;
}
