private string id;

void set_power_id(string i) {
    id = i;
}

int main() {
    this_player()->queue_power(id);
}