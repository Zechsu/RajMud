#include <lib.h>
#include <armor_layers.h>

inherit LIB_ARMOR;

void create() {
    ::create();
    set_short("golden ring");
    set_long("It's a golden ring for testing purposes.");
    set_ids(({"ring"}));
    set_adjectives(({"gold", "golden"}));
    set_required_limbs(({"hand"}));
    set_layer(A_RING);
}

varargs mixed query_real_limbs(string* args, int slot) {
    object tp = this_player();
    // List of all limbs we will need (not severed)
    string* limbs = this_player()->find_limb(args, 1);
    string* required = query_required_limbs();
    string* ret = ({});

    if (slot) {
        foreach (string limb in limbs) {
            if (sizeof(tp->query_worn(limb, query_layer())) == Race(tp->query_race())->query_fingers(limb)) {
                limbs -= ({limb});
            }
        }
    }

    foreach (string req in required) {
        for (int i = 0; i < sizeof(limbs); i++) {
            if (strsrch(limbs[i], req) > -1) {
                ret += ({limbs[i]});
                limbs -= ({limbs[i]});
                break;
            }
        }
    }

    return ret;
}