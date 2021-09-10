#include <command.h>

int main(string arg) {
    string desc;
    string exits = "";
    object room = environment(this_player());
    string* exit_keys = keys(room->query_exits());
    
    if (sizeof(exit_keys) == 1) {
        exits = exit_keys[0];
    }
    else {
        foreach (string exit in exit_keys) {
            exits = exits + exit + " ";
        }
    }
    desc = room->query_short() + " [" + exits + "]\n" + room->query_long() + "\n";
    write(desc);
    return 1;
}
