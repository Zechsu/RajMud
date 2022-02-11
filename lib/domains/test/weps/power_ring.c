#include <lib.h>
#include <armor_layers.h>

inherit "/std/obj/ring";

void create() {
    ::create();
    set_short("ring of power");
    set_long("It's a power ring for testing purposes.");
    set_ids(({"ring of power", "power ring", "ring", "power"}));
    set_required_limbs(({"hand"}));
    set_layer(A_RING);
}

varargs mixed event_wear(object who, string* limbs) {
    this_player()->set_visible(0);
    return ::event_wear(who, limbs);
}

varargs mixed event_remove(int quietly) {
    this_player()->set_visible(1);
    tell_room(environment(this_player()), this_player()->query_name() + " appears out of thin air!\n", ({this_player()}));
    return ::event_remove(1);
}
