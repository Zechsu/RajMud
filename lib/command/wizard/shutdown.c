#include <command.h>

int
main(string arg)
{
    // Save users characters before shutdown
    foreach(object u in users()) {
        u->save_player();
    }
    shutdown(0);
    return 1;
}
