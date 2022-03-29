#include <lib.h>
#include <armor_layers.h>

inherit LIB_WEAPON;

int engaged = 0;
string* sound = ({"Tsuuuun~\n", "SHPRIING~\n"});

void create() {
    ::create();
    set_short("bagira otf knife");
    set_long("Highest quality the market has to offer.");
    set_ids(({"bagira otf knife", "otf knife", "knife", "otf"}));
    set_required_limbs(({"hand"}));
    set_layer(-1);
}

void init() {
    add_action("do_engage", "engage");
    add_action("do_disengage", "disengage");
}

int do_engage(string arg) {
    if (!arg || trim(arg) == "")
	    return 0;

    if (engaged)
	    return notify_fail("It's already out.\n");

    engaged = 1;
    set_layer(A_WEAPON);
    tell_room(environment(this_player()), element_of(sound));
    return 1;
}

int do_disengage(string arg) {
    if (!arg || trim(arg) == "")
        return 0;

    if (!engaged)
        return notify_fail("It's not engaged.\n");

    engaged = 0;
    set_layer(-1);
    tell_room(environment(this_player()), element_of(sound));
    return 1;
}

string query_attack_message() {
    return "$N $vswing at $T";
}
