private int max_level;
private string name;

void create() {
    if (!max_level) {
        max_level = 5;
    }
}

void set_max_level(int m) {
    max_level = m;
}

int query_max_level() {
    return max_level;
}

void set_name(string n) {
    name = n;
}

string query_name() {
    return name;
}