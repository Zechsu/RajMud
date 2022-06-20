inherit "/std/skill";

void create() {
    set_name("lumbering");
    set_max_level(2);
}

int required_exp(int level) {
    return level * 100;
}