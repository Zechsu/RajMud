#include <command.h>

int main(string arg) {
    string desc;
    desc = environment(this_player())->query_short();
    write(desc + "\n");
    return 1;
}