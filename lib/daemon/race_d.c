#include <globals.h>

mapping races = ([]);

void create() {
    foreach (string file in get_dir(RACES_DIR + "/*.c")) {
        string tmp = RACES_DIR + "/" + file;
        string name;

        if (!load_object(tmp)) {
            continue;
        }
        name = tmp->query_race_name();
        races[name] = tmp;
    }
}

string query_race_filename(string race) {
    return races[race];
}

string* query_races() {
    return keys(races);
}

mapping query_race_data() {
    return copy(races);
}
