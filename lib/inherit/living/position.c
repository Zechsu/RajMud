#include <globals.h>
#include <positions.h>
#include "../include/body.h"

private int position;

// Prototype functions
string query_name();
string query_race();
int query_trait(string trait);      // m_traits

void create() {
    if (!position || position == 0) {
        position = STANDING;
    }
}

void set_position(int pos) {
    position = pos;
}

int query_position() {
    return position;
}

int can_stand() {
    string* legs = Race(query_race())->query_legs();
    mapping body = query_body();
    foreach (string leg in legs) {
        if (!body[leg]["severed"]) {
            return 1;
        }
    }
    return notify_fail("You have no support to stand on.\n");
}

int event_stand() {
    if (!can_stand()) {
        return 0;
    }
    if (position == STANDING) {
        return notify_fail("You're already standing.\n");
    }
    write("You stand.\n");
    say(this_player()->query_name() + " stands.\n");
    position = STANDING;
    return 1;
}

int event_crawl() {
    if (position != CRAWLING) {
        position = CRAWLING;
        write("You start crawling on the ground.\n");
        say(query_name() + " starts crawling on the ground.\n");
    }
    return 1;
}

int can_fly() {
    if (position == FLYING) {
      return notify_fail("You're already flying.\n");
    }
    if (query_trait("flight") == 0) {
        return notify_fail("You can't fly!\n");
    }
    return 1;
}

int event_fly() {
    if (!can_fly()) {
      return 0;
    }
    write("You begin to fly.\n");
    say(this_player()->query_name() + " flies up.\n");
    position = FLYING;
    return 1;
}

varargs int can_sit(object on) {
    return 1;
}

int event_sit() {
    if (!can_sit()) {
        retur 0;
    }
    write("You sit down.\n");
    say(this_player()->query_name() + " sits down.\n");
    position = SITTING;
    return 1;
}

void check_position() {
    if (!can_stand()) {
        event_crawl();
    }
}
