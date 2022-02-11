private int visible;

void create() {
    if (!visible || visible == 0) {
        visible = 1;
    }
}

void set_visible(int i) {
    visible = i <= 0? 0 : 1;
}

int is_visible() {
    return visible;
}