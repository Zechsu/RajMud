#include <globals.h>

private string short_desc;

void create() {

}

int set_short(string short) {
    short_desc = short;
}

string query_short() {
    return short_desc;
}