#include <positions.h>
#include <daemons.h>
#include <armor_layers.h>
#include <flags/room_flags.h>
#include <descriptors/attack.h>

private nosave object* attackers;
private nosave object* enemies;
private string target_limb;

void create() {
    enemies = ({});
    attackers = ({});
}

object query_enemy() {
    return sizeof(enemies)? enemies[0] : 0;
}

object* query_enemies() {
    return sizeof(enemies)? enemies : 0;
}

void stop_combat() {
    enemies = ({});
    set_heart_beat(0);
}

void add_enemy(object enemy) {
    if (enemy) {
        if (member_array(enemy, enemies) > -1) {
            write("You're already attacking him.\n");
            return;
        }
        enemies += ({enemy});
        set_heart_beat(2);
    }
    else {
        debug_message("Invalid enemy object in add_enemy()");
    }
}

void remove_enemy(object enemy) {
    if (enemy) {
        enemies -= ({enemy});
    }
    if (!sizeof(enemies)) {
        set_heart_beat(0);
    }
}

int can_start_attack(object target) {
    if (environment(this_player())->query_flag(ROOM_NO_COMBAT)) {
        write("You can't fight here!\n");
        return 0;
    }
    if (userp(target) && environment(this_player())->query_flag(ROOM_NO_PK)) {
        write("You can't attack other players in this area!\n");
        return 0;
    }

    return 1;
}

int can_attack(object target) {
    if (!target) {
        return 0;
    }
    if (member_array(target, enemies) == -1) {
        return 0;
    }
    // if (this_player()->query_position() != STANDING) {
    //     write("You need to be standing to attack.\n");
    //     return 0;
    // }
    if (environment(target) != environment(this_player())) {
        write("The target is not here.\n");
        return 0;
    }

    return 1;
}

void do_weapon_attack(object target) {
    object weapon;
    string* mess, tmp;
    int damage, res;
    weapon = this_player()->query_worn(0, A_WEAPON)[0];
    damage = weapon->event_strike(target);

    // Query an unsevered limb
    target_limb = target->query_random_limb(1);

    // If enemy has no unsevered lims, remove it as an enemy
    if (!target_limb) {
        remove_enemy(target);
        return;
    }

    // if (target->is_limb_severed(target_limb)) {
    //     target_limb = target->query_random_limb(1);
    //     // if target has no more limbs left remove him from enemies
    //     if (!target_limb) {
    //         remove_enemy(target);
    //         return;
    //     }
    // }

    //tmp = weapon->query_attack_message();
    // compose_message() does not support $L.
    //tmp = replace_string(tmp, "$L", target_limb);
    
    // mess = compose_message(this_player(), tmp, target, ({weapon}));
    mess = Attack(weapon->query_attacks()[0])->describe(([
        ATTACKER    : this_player(),
        DEFENDER    : target,
        WEAPON      : weapon,
        LOCATION    : target_limb
    ]));

    mess = map(mess, (: "\n    " + capitalize($1) + "\n\n" :));
    tell_object(this_player(), mess[0]);
    tell_object(target, mess[1]);
    tell_room(environment(target), mess[2], ({this_player(), target}));
    res = target->event_receive_damage(damage, target_limb);
    if (res == -1) {
        remove_enemy(target);
    }
    // target->event_receive_damage(damage, target_limb);
}

void do_unarmed_attack(object target) {
    float damage = 1;
    string* mess, tmp;

    target_limb = target->query_random_limb(1);

    // If enemy has no unsevered lims, remove it as an enemy
    if (!target_limb) {
        remove_enemy(target);
        return;
    }

    tmp = Race(this_object()->query_race())->query_attack_message();
    if (!tmp) {
        return;
    }
    // compose_message() does not support $L.
    tmp = replace_string(tmp, "$L", target_limb);

    mess = compose_message(this_player(), tmp, target);

    tell_object(this_player(), mess[0] + sprintf(" [%f]\n", damage));
    tell_object(target, mess[1] + "\n");
    tell_room(environment(target), mess[2] + "\n", ({this_player(), target}));
    target->event_receive_damage(damage, target_limb);
}

int event_attack(object target) {
    if (!target) return 0;
    
    if (!target_limb) {
        target_limb = target->query_random_limb(1);
    }

    if (!can_start_attack(target)) {
        return 1;
    }
    // add target as enemy
    add_enemy(target);
    // make target also attack us
    target->add_enemy(this_player());
    return 1;
}

void set_target_limb(string limb) {
    target_limb = limb;
}

int is_in_combat() {
    return sizeof(enemies) > 0;
}

void heart_beat() {
    object target = element_of(enemies);
    if (!sizeof(enemies)) {
        set_heart_beat(0);
        return;
    }
    if (!can_attack(target)) {
        set_heart_beat(0);
        enemies -= ({target});
        return;
    }
    if (sizeof(this_player()->query_worn(0, A_WEAPON))) {
        return do_weapon_attack(target);
    }
    else {
        return do_unarmed_attack(target);
    }
    // If we get to this point, it means we couldn't have done any attack, so we stop the combat
    remove_enemy(target);
}
