inherit "/std/skill";

void create() {
    set_name("sword");
    set_max_level(350);
}

int required_exp(int level) {
    return level * 100;
}