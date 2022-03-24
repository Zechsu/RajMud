#include <lib.h>
#include <armor_layers.h>
#include <positions.h>

inherit "/std/obj/ring";

void create() {
    ::create();
    set_short("%^BOLD%^YELLOW%^golden ring of flight%^RESET%^");
    set_long("It's a ring that magically makes you fly after putting it on.");
    set_ids(({"ring"}));
    set_adjectives(({"gold", "golden"}));
    set_required_limbs(({"hand"}));
    set_layer(A_RING);
}

varargs mixed event_wear(object who, string* limbs) {
    this_player()->add_trait("flight", 1);
    return ::event_wear(who, limbs);
}


varargs mixed event_remove(int quietly) {
    write("You gracefully float down to the ground.\n");
    this_player()->subtract_trait("flight", 1);
    return ::event_remove(quietly);
}
