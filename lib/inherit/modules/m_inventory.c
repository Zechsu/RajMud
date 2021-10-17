#include <globals.h>

private nosave mapping inventory = ([]);
private int capacity;
private int item_count;

protected void event_load_item(string file, mixed args, int count);

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

int is_full() {
    return item_count == capacity;
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

protected void event_load_inventory() {
    int filtersize, i;
    object* stuff, *items, *tmp;

    stuff = all_inventory(this_object());
    items = ({});

    for (i = 0; i < sizeof(stuff); i++) {
        if (tmp = ({base_name(stuff[i])})) items += tmp;
    }
    filtersize = 0;

    foreach (string file, mixed args in inventory) {
        for (i = 0; i < sizeof(items); i++) {
            if (base_name(items[i]) == file) filtersize++;
        }
        event_load_item(file, args, filtersize);
        filtersize = 0;
    }
}

protected void event_load_item(string file, mixed args, int count) {
    object ob;
    int u;

    if (functionp(args)) args == evaluate(args);

    if (intp(args)) {
        if (args < 0) {
            args = 1;
            u = 1;
        }
        args = args - count;
        while (args > 0) {
            ob = new(file);
            if (ob) {
                ob->move_object(this_object());
            }
            args--;
        }
    }
}