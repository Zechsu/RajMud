#include <lib.h>
#include <attributes.h>

inherit LIB_LIVING;

void create() {
    ::create();
    set_short("goblin spearmann");
    set_name("goblin spearman");
    set_race("goblin");
    set_ids(({"goblin spearman", "goblin spear", "spearman", "goblin"}));
    set_gender(1);
    setup();
    set_skill_level("spear", 15);
    set_attribute(NORMAL_STRENGTH, 30);

    add_object("/domains/goblincave/weps/spear")->event_quiet_wear(this_object());

}