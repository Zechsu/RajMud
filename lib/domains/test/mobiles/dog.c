#include <lib.h>
#include <attributes.h>

inherit LIB_LIVING;

void create() {
    ::create();
    set_short("dog");
    set_name("dog");
    set_race("goblin");
    set_ids(({"dog"}));
    set_gender(1);
    setup();
}

mixed event_hear(mixed source, string mess) {
    if (strsrch(mess, "bark") != -1) {
        force_me("say bark bark");
    }
    ::event_hear(this_object(), mess);
}