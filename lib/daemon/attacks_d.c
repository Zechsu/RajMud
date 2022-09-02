#include <globals.h>
#include <daemons.h>

private mapping attacks = ([]);

void create() {
    foreach (string file in get_dir(ATTACKS_DIR + "*.c")) {
        string tmp = ATTACKS_DIR + file;

        if (!load_object(tmp)) {
            debug_message("Couldn't load attack " + tmp + "\n");
            continue;
        }

        attacks[file[0..<3]] = tmp;
    }
}

string query_attack(string attack) {
    return attacks[attack];
}

void debug_me() {
    debug_message(sprintf("%O", attacks));
}