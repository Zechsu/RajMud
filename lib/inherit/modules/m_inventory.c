private int capacity;
private int item_count;

void create() {
    capacity = -1;
}

int query_inventory_capacity() {
    return capacity;
}

void set_inventory_capacity(int cap) {
    capacity = cap;
}

int is_inventory_full() {
    if (capacity == -1) {
        return 0;
    }
    return sizeof(all_inventory()) == capacity;
}

object query_item_from_inventory(string item) {
    object ob;
    if (ob = present(item, TO)) {
        return ob;
    }
    return 0;
}