#include <globals.h>

private string short_description;
private string long_description;

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