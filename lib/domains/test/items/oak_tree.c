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
    if (!who) {
        who = TP;
    }
    if (::event_gather(who)) {
        write("You cut the oak tree.\n");
        //TODO: compose it
        say(TP->query_name() + " cuts the oak.\n");
        who->give_exp("lumbering", query_exp_reward());     
        return 1;
    }
    return 0;
}