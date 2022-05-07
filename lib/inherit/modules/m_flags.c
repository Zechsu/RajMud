int flags;

void set_flag(int flag) {
    flags |= flag;
}

void toggle_flag(int flag) {
    flags ^= flag;
}

void remove_flag(int flag) {
    flags &= ~flag;
}

int query_flag(int flag) {
    return flags & flag;
}