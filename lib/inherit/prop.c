#include <globals.h>

private string long_desc;
private string id;

void create() {
    
}

int set_long(string desc) {
    long_desc = desc;
}

string query_long() {
    return long_desc;
}

int set_id(string new_id) {
    id = new_id;
}

string query_id() {
    return id;
}

int id(string arg) {
    return arg == id;
}

void move(mixed dest) {
    move_object(dest);
}

int is_prop() {
    return 1;
}
