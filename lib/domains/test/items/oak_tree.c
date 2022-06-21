#include <lib.h>

inherit LIB_GATHERABLE;

void create() {
    ::create();
    set_short("oak tree");
    set_long("It's an oak tree. You could cut it.");
    set_ids(({"oak", "tree", "oak tree"}));
    set_action("cut");
    set_drop("/std/obj/gatherables/oak");
    set_drop_amount(10000 + random(25001));
    set_exp(1);
}
int can_gather(object who) {
    if (who->query_race() == "beaver") {
        return 1;
    }
    if (!sizeof(filter_array(who->query_wield(), (: $1->is_lumbering_tool() :))) > 0) {
        return notify_fail_colored("%^RED%^You lack the tools required.%^RESET%^\n");
    }
    return ::can_gather(who);
}

mixed event_gather(object who) {
    string* mess = compose_message(who, "$N $vcut the oak tree.");
    if (!can_gather(who)) {
        return 0;
    }

    tell_object(who, capitalize(mess[0]) + "\n");
    tell_room(environment(who), capitalize(mess[1]) + "\n", ({who}));

    who->give_exp("lumbering", query_exp_reward());
    get_drop(who);
    remove();

    return 1;
}