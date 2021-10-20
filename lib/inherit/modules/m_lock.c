#include <globals.h>

int locked;

// TODO: figure out how to make use of these different return types as error messages or some sort.
mixed do_lock(object who, object key) {
    if (!key) {
        return "You do not have a key.\n";
    }
    if (!who) {
        who = this_player();
    }
    if (locked) {
        return "It is locked already.\n";
    }
    locked = 1;
    return 1;
}
