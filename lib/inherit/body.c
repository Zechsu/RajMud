#include <globals.h>

private string short_desc;
private string* inventory;
private mapping traits = ([]);

void create() {
    if (!sizeof(traits)) {
        traits = ([]);
    }
}

string* query_inventory() {
    return inventory;
}

int set_inventory(string* inv) {
    inventory = inv;
    return 1;
}

void set_short(string new_short) {
    short_desc = new_short;
}

string query_short() {
    return short_desc;
}

int get_item(mixed item) {
    item->move(this_player());
    inventory += ({base_name(item)});
}

mapping query_traits() {
    return traits;
}

int query_trait(string trait) {
    if (traits[trait]) {
        return traits[trait];
    }
    else {
        return 0;
    }
}

int set_trait(string trait, mixed value) {
    traits[trait] = value;
    return 1;
}