#include <globals.h>

inherit LIB_ITEM;

void create() {
    ::create();
    set_short("beetle analyzer");
    set_long("Use this tool on a fighter beetle to see its stats.");
    set_ids(({"analyzer", "beetle analyzer"}));
}

void init() {
    add_action("do_analyze", "analyze");
}

int do_analyze(string str) {
    object ob;
    int attack, hp, max_hp;
    if (!str) {
        return notify_fail("Analyze what?\n");
    }

    if (ob = present(str, this_player())) {
        attack = ob->query_skill_level("attack");
        hp = ob->query_skill_level("health");
        max_hp = ob->query_skill_level("max_health");
        write(sprintf("It's got %d attack and %d out of %d hit points\n", attack, hp, max_hp));
        return 1;
    }

    return notify_fail("You must have a beetle to analyze it.\n");
}