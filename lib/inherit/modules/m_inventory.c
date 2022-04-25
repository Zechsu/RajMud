private int capacity = -1;
private int item_count;

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

void move_inventory_to(object target) {
    object* inv = all_inventory(this_object());
    foreach (object ob in inv) {
        ob->move(target);
    }
}

void restore_worn_equipment() {
    object* worn;

    if (!clonep())
        return;

    worn = all_inventory(this_player());
    worn = filter_array(worn, (: $1->query_worn() :));

    if (!worn)
        return;

    foreach (object item in worn) {
        item->set_limb_worn();
    }
}