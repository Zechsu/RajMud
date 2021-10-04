#include <globals.h>

private string description;
private string id;

void create() {
    
}

int set_description(string desc) {
    description = desc;
}

string query_description() {
    return description;
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
