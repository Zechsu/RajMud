#include <globals.h>

inherit "/std/obj/beetle";

mixed rubber_soul() {
    int dmg = get_damage();
    query_target()->take_damage(dmg);
    heal(dmg);
    return "Ringo beetle [" + query_owner() + "] used 「Rubber Soul」\n";
}

void create() {
    ::create();
    set_short("ringo");
    set_long("Personal favourite of PepperCbj!");
    set_ids(({"beetle", "ringo", "ringo beetle"}));
    set_special_attack((: rubber_soul :));
    set_special_attack_chance(100);
}
