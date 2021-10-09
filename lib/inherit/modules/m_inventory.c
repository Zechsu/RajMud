#include <globals.h>

private mapping inventory;
private int capacity;
private int item_count;

void create() {
    if (!inventory) {
        inventory = ([]);
    }
}

mapping query_inventory() {
    return inventory;
}

int query_capacity() {
    return capacity;
}

void set_capacity(int cap) {
    capacity = cap;
}

int set_inventory(mapping inv) {
    inventory = inv;
    return 1;
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

    inventory[base_name(item)] += 1;
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