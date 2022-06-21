#include <lib.h>
#include <armor_layers.h>

inherit LIB_ARMOR;

void create() {
    ::create();
    set_short("steel teeth");
    set_long("It's a pair of pointy steel teeth. Use it to cut trees.");
    set_ids(({"teeth", "steel", "steel teeth"}));
    set_required_limbs(({"head"}));
    set_layer(A_TEETH);
}

// FIXME: Implement race "groups" so all rodents can wear these not just beavers
mixed can_wear(object who, string* limbs) {
    if (who->query_race() != "beaver") {
        return notify_fail("These are not for you!\n");
    }
    return ::can_wear(who, limbs);
}

int is_mining_tool() {
    return 1;
}