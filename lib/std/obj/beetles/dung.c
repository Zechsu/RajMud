#include <globals.h>

inherit "std/obj/beetle";

string do_special() {
    query_target()->take_damage(2);
    return "dung beetle throws some shit around\n";
}

void create() {
    ::create();
    set_short("dung beetle");
    set_long("A lovely dung beetle!");
    set_ids(({"beetle", "dung", "dung beetle"}));
    set_special_attack((:do_special:));
    set_special_attack_chance(20);
}
