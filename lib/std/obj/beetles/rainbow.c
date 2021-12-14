#include "colors.h"

inherit "std/obj/beetle";

string make_rainbow(string sh);

void create() {
    ::create();
    set_short(make_rainbow("rainbow beetle"));
    set_ids(({"rainbow", "rainbow", "beetle"}));
}

string make_rainbow(string sh) {
    string str = "";
    for (int i = 0; i < sizeof(sh); i++) {
        str += RAINBOW_ARR[i % 7] + sh[i..i];
    }
    return str + white();
}
