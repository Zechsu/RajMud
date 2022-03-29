#include <lib.h>

inherit LIB_LIVING;

void create() {
    ::create();
    set_short("sewer rat");
    set_name("sewer rat");
    set_ids(({"rat", "sewer rat"}));
    set_race("rodent");
    set_gender(1);
    set_skill_level("constitution", 1);
    setup();
}