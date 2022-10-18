#include <globals.h>

void rebuild_races();

mapping races = ([]);

void create() {
    rebuild_races();
}

void rebuild_races() {
    foreach (string file in get_dir(RACES_DIR + "/*.c")) {
        string tmp = RACES_DIR + "/" + file;
        string name;

        if (!load_object(tmp)) {
            debug_message("Couldn't load race " + tmp + "\n");
            continue;
        }
        name = tmp->query_race_name();
        races[name] = tmp;
    }
}

int is_valid_race(string race) {
    return races[race]? 1 : 0;
}

string query_race_file(string race) {
    return races[race];
}

string* query_races() {
    return keys(races);
}

mapping query_race_data() {
    return copy(races);
}
