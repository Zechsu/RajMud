#include "include/m_decay.h"

private int decay_time = 10;
private int decay;

void create() {
    if (clonep() && !decay) {
        set_decay(1);
    }
    this_object()->add_save(({"decay", "decay_time"}));
}

void set_decay(int dec) {
    remove_call_out();
    decay = dec;
    call_out("decay", decay_time);
}

void event_decay() {
    if (environment(this_object())->is_living()) {
        tell_object(this_object(), sprintf("%s decays.\n", capitalize(this_object()->query_short())));
    }
    else {
        tell_room(environment(this_object()), sprintf("%s decays.\n", capitalize(this_object()->query_short())));
    }
    this_object()->remove();
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