#include <lib.h>
#include "../def.h"

inherit LIB_ROOM;

void create() {
    set_short("Kocinoffs room");
    set_long("No one knows what's inside. It is speculated however that that a huge arsenal of oversized dildos can be found there.");
    add_exit("south", __DIR__ + "kicata_sublekalni");
	add_prop("dildos", "There is a wide selection of all sorts of dildos ranging from 30cm bbc to 7m dildos.");
    add_item(AREA_ITEMS + "7m_dildo");
    add_item(AREA_ITEMS + "dildo");
}
