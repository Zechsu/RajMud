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

string query_wielded() {
    object* equips = all_inventory(this_object());
    object* wielded = filter_array(equips, (:$1->query_wielded():));
    if (sizeof(wielded)) {
        return sprintf("%s is wielding %s in %s %s", capitalize(this_object()->query_pronoun()), wielded[0]->query_short(), this_object()->query_possessive_determiner(), wielded[0]->query_wielded());
    }
    return 0;
}