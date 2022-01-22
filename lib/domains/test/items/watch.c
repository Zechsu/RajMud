#include <lib.h>
#include <daemons.h>

inherit LIB_ITEM;

void create() {
    ::create();
    set_short("watch");
    set_ids(({"watch"}));
}

string query_long() {
    int hour = NATURE_D->query_hour();
    if (hour == 12) {
        return "It shows 12 PM.";
    }
    else if (hour == 24) {
        return "It shows 12 AM.";
    }
    else if (hour > 12) {
        return sprintf("It shows %d PM.", hour%12);
    }
    else {
        return sprintf("It shows %d AM.", hour);
    }
}