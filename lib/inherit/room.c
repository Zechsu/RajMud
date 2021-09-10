#include <globals.h>

private string short_description;
private string long_description;
private mapping exits = ([]);

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

void add_exit(string direction, string destination) {
    if (!exits[direction]) {
        exits[direction] = destination;
    }
}

void set_exits(mapping new_exits) {
    exits = new_exits;
}

void remove_exit(string exit) {
    if (exits[exit]) {
        map_delete(exits, exit);
    }
}

mapping query_exits() {
    return exits;
}