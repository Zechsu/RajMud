#include <lib.h>
#include <modules.h>

inherit LIB_ITEM;
inherit M_WIELDABLE;

void create() {
    ::create();
    set_short("testsword");
    set_long("A sword for testing, obviously");
    set_ids(({"testsword"}));
    set_required_limbs(({"hand"}));
    set_handed(1);
}