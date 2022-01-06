#include <globals.h>

inherit "std/obj/beetle";

string do_special() {
    object target = query_target();
    target->take_damage(2);
    return sprintf("%s [%s] throws dung at %s [%s]\n", query_short(), query_owner(), target->query_short(), target->query_owner());
}

void create() {
    ::create();
    set_short("dung");
    set_long("A bit smelly but at the same time very skillful.");
    set_ids(({"beetle", "dung", "dung beetle"}));
    set_special_attack((:do_special:));
    set_special_attack_chance(20);
}
