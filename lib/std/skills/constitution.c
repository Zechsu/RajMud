inherit "/std/skill";

void create() {
    set_name("constitution");
    set_max_level(5);
}

int required_exp(int level) {
    return level * 100;
}