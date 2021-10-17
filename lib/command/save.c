#include <command.h>

int main(string str) {
    object tp = this_player();

    tp->save_player();
    write("Saved player.\n");

    return 1;
}