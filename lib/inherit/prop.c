#include <globals.h>

inherit CLEAN_UP;

private string description;
private string key;

void create() {
    
}

int set_description(string desc) {
    description = desc;
}

string query_description() {
    return description;
}

int set_key(string new_key) {
    key = new_key;
}

string query_key() {
    return key;
}

int key(string arg) {
    return arg == key;
}

void move(mixed dest) {
    move_object(dest);
}

int is_prop() {
    return 1;
}
