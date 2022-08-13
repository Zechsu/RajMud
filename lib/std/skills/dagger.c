inherit "/std/skill";

void create() {
    set_name("dagger");
    set_max_level(350);
}

int required_exp(int level) {
    return level * 100;
}