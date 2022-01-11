#include <globals.h>
#include <positions.h>
#include "../include/body.h"

private int position;

// Prototype functions
string query_name();
string query_race();

void create() {
    if (!position || position == 0) {
        position = 1;
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
    write("You stand up.\n");
    position = STANDING;
    return 1;
}

int event_crawl() {
    position = CRAWLING;
    write("You start crawling on the ground.\n");
    return 1;
}

void check_position() {
    if (!can_stand()) {
        event_crawl();
    }
}