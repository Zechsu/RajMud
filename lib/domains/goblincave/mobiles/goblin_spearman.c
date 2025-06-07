#include <lib.h>
#include <attributes.h>

inherit LIB_LIVING;

void create() {
    ::create();
    set_short("goblin spearman");
    set_name("goblin spearman");
    set_race("goblin");
    set_ids(({"goblin spearman", "goblin spear", "spearman", "goblin"}));
    set_gender(1);
    setup();
    // 15 was default, increased for testing purposes
    set_skill_level("spear", 150);
    set_attribute(NORMAL_STRENGTH, 30);
    // Had no constituion 100 for testing, idk normal value
    set_attribute(NORMAL_CONSTITUTION, 100);

    add_object("/domains/goblincave/weps/spear")->event_quiet_wear(this_object());
}