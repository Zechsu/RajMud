#include <command.h>

int main(string arg) {
    int res = this_player()->toggle_godmode();
    if (res == 1) {
        tell_object(this_player(), "Godmode enabled\n");
    }
    else {
        tell_object(this_player(), "Godmode disabled\n");
    }
    return 1;
}