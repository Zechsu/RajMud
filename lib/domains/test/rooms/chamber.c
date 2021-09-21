#include <globals.h>

inherit LIB_ROOM;

void create() {
    ::create();
    set_short("The Chamber of Secrets");
    set_long("Ay yo kicata ne e Hogwarts. There's a button on the wall.");
    add_exit("out", "/domains/test/rooms/kicatabath");
}

void init() {
    add_action("do_push", "push");
}

int do_push(string str) {
    if (!str || trim(str) == "") {
        return 0;
    }
    if (str == "button" || str == "the button") {
        tell_object(this_player(), "The entrance closes up\n");
        "/domains/test/rooms/kicatabath"->remove_exit("in");
        remove_exit("out");
        return 1;
    }
    return 0;
}