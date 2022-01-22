#include <modules.h>
#include <lib.h>

inherit LIB_ARMOR;

void create() {
    ::create();
    set_short("plain pants");
    set_long("It's a pair of plain pants for testing purposes.");
    set_ids(({"pants", "plain pants"}));
    set_required_limbs(({"leg", "leg"}));
}