#include <globals.h>

inherit LIB_ITEM;

void create() {
    ::create();
    set_short("kabuto analyzer");
    set_long("Use this tool on a kabuto to identify it and see its stats.");
    set_ids(({"analyzer", "kabuto analyzer"}));
}

void init() {
    add_action("do_analyze", "analyze");
}

int do_analyze(string str) {
    object* inv = all_inventory(this_player());
    int num = 0;

    if (!str) {
        return notify_fail("Analyze what?\n");
    }

    if (str == "kabuto") {
        inv = filter_array(inv, (: $1->is_kabuto() :));
        if (sizeof(inv) != 0) {
            write("The " + inv[0]->query_short() + " has " + inv[0]->query_health() + " health points and " + inv[0]->query_attack() + " attack.\n");
            write("It's " + inv[0]->query_specie() + "!\n");
            return 1;
        }
    }
    else if (sscanf(str, "kabuto.%d", num) == 1) {
        inv = filter_array(inv, (: $1->is_kabuto() :));
        if (num <= 0) {
            if (sizeof(inv) != 0) {
                write("The " + inv[0]->query_short() + " has " + inv[0]->query_health() + " health points and " + inv[0]->query_attack() + " attack.\n");
                write("It's " + inv[0]->query_specie() + "!\n");
                return 1;
            }
        }
        if (sizeof(inv) >= num) {
            write("The " + inv[num-1]->query_short() + " has " + inv[num-1]->query_health() + " health points and " + inv[num-1]->query_attack() + " attack.\n");
            write("It's " + inv[num-1]->query_specie() + "!\n");
            return 1;
        }
        else {
            return notify_fail("You do not have that many kabutos.\n");
        }
    }
    return notify_fail("You must have a kabuto to analyze it.\n");
}