#include <globals.h>

private object* weapon_types = ({});

void create() {
    mixed input = read_file("include/weapon_types.h");
    int count;
    input = explode(input, "\n");
    input = filter(input, (: $1 != "" :));
    input = input[2..<2];
    if (!sscanf(input[0], "#define WEAPON_TYPES_COUNT %d", count)) {
        debug_message("FAILED TO LOAD WEAPON_TYPES COUNT");
        return;
    }

    weapon_types = allocate(count);
    for (int i = 1; i < sizeof(input); i++) {
        int id;
        string type;
        sscanf(input[i], "#define WEAPON_%s %d", type, id);
        weapon_types[id-1] = load_object("/std/weapon_types/" + lower_case(type));
    }
}

object* debug_me() {
    return weapon_types;
}

object query_weapon_type(int id) {
    return weapon_types[id-1];
}