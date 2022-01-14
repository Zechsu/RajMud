private nosave object* enemies;

void create() {
    enemies = ({});
}

object query_enemy() {
    return sizeof(enemies)? enemies[0] : 0;
}

void add_enemy(object enemy) {
    if (enemy) {
        enemies += ({enemy});
    }
    else {
        debug_message("Invalid enemy object in add_enemy()");
    }
}


void heart_beat() {
    if (!sizeof(enemies)) {
        set_heart_beat(0);
        return;
    }
}