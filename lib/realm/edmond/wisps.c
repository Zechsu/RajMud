#include <lib.h>

inherit LIB_ITEM;

void create() {
    ::create();
    set_short("%^YELLOW%^wisps of holy energy%^RESET%^");
    set_long("It is nondescript");
    set_ids(({"wisps", "wisps of holy energy"}));
    set_heart_beat(3);
}

int can_get() {
    return 0;
}

void heart_beat() {
    object env = environment(this_object());
    object* livings;

    if (!env)
        return;

    livings = filter_array(all_inventory(env), (: $1->is_living() :));
    if (sizeof(livings)) {
        foreach (object liv in livings) {
            string limb = liv->query_random_damaged_limb();

            if (!limb)
                continue;

            if (liv->event_heal_limb(limb)) {
                tell_object(liv, sprintf("%s rejuvenate your %s.\n", query_short(), limb));
            }
        }
    }
}