#include <globals.h>

private mapping limbs;

void create() {
    if (!sizeof(limbs)) {
        limbs = ([]);
    }
}

int set_limbs(mapping new_limbs) {
    limbs = new_limbs;
    return 1;
} 