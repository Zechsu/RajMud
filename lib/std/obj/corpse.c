#include <lib.h>

inherit LIB_ITEM;

private int decay;
private int decay_time = 10;
private int set_decay(int dec);

void create() {
    ::create();
    if (!query_short()) {
        set_short("corpse");
    }
    if (!query_long()) {
        set_long("The corpse of someone.");
    }
    if (!sizeof(query_ids())) {
        set_ids(({"corpse"}));
    }
    if (clonep() && !decay) {
        set_decay(1);
    }
    add_save(({"short_desc", "long_desc", "decay", "decay_time", "ids"}));
}

void set_decay(int dec) {
    remove_call_out();
    decay = dec;
    call_out("decay", decay_time);
}

void event_decay() {
    object env = environment(TO);
    if (env->is_living()) {
        tell_room(ENV(env), sprintf("%s decays.\n", capitalize(query_short())));
    }
    else {
        tell_room(ENV(TO), sprintf("%s decays.\n", capitalize(query_short())));
    }
    remove();
}

void decay() {
    decay--;
    if (decay > 0) {
        call_out("decay", decay_time);
    }
    else {
        event_decay();
    }
}