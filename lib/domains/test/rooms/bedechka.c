#include <globals.h>

inherit LIB_ROOM;
inherit M_SEARCH;

void create() {
    ::create();
    set_short("Bedechka lake");
    set_long("A small lake. There might be beetles around.");
    set_search_table(([0:85, "std/obj/beetles/dung":14, "std/obj/beetles/rainbow":1]));
    add_exit("south", "domains/sshapkata/rooms/shapka");
}
