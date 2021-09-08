#include <globals.h>
#include "def.h"

private string short_description;
private string long_description;
private mapping exits;

void create() {

}

void set_short(string short) {
    short_description = short;
}

void set_long(string long) {
    long_description = long;
}

string query_short() {
    return short_description;
}

string query_long() {
    return long_description;
}

void add_exit(string direction, string room_path) {
    exits[direction] = room_path;
}

void remove_exit(string exit) {
    map_delete(exits, exit);
}

mapping query_exits() {
    return exits;
}