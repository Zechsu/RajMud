#include <globals.h>

private string short_desc;
private mapping inventory;
private mapping traits = ([]);

void create() {
    if (!sizeof(traits)) {
        traits = ([]);
    }
}

mapping query_inventory() {
    return inventory;
}

int set_inventory(mapping inv) {
    inventory = inv;
    return 1;
}

void set_short(string new_short) {
    short_desc = new_short;
}

string query_short() {
    return short_desc;
}

object query_item_from_inventory(string item) {
    foreach(object ob in all_inventory(this_player())) {
        if (ob->id(item)) {
            return ob;
        }
    }
    return 0;
}

int add_item_to_inventory(mixed item, int amount) {
    if (!amount) {
        amount = 1;
    }

    inventory[base_name(item)] += amount;
    return 1;
}

int remove_item_from_inventory(mixed item) {
    string basename = base_name(item);

    if (inventory[basename]) {
        inventory[basename] -= 1;
        if (inventory[basename] <= 0) {
            map_delete(inventory, basename);
        }
        return 1;
    }
    
    return 0;
}

int query_item_amount(mixed item) {
    return inventory[base_name(item)];
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