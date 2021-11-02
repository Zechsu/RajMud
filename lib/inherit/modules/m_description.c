#include <globals.h>
#include <daemons.h>

private string short_desc;
private string long_desc;

void create() {
    if (!short_desc) {
        short_desc = 0;
    }
    if (!long_desc) {
        long_desc = 0;
    }
}

int set_short(string new_short) {
    short_desc = new_short;
    return 1;
}

int set_long(string new_long) {
    long_desc = new_long;
    return 1;
}

string query_short() {
    return short_desc;
}

string query_long() {
    return long_desc;
}
