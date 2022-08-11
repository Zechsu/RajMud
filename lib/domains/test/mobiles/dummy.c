#include <lib.h>

inherit LIB_LIVING;

void create() {
    ::create();
    set_short("Damage dummy");
    set_name("Damage dummy");
    set_race("dummy");
    set_ids(({"dummy", "damage dummy"}));
    set_gender(1);
    setup();
}

varargs int event_receive_damage(float damage, string limb) {
    this_object()->force_me("say I got hit for " + damage + "!");
}