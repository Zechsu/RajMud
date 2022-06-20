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

mixed event_gather(object who) {
    if (!who) {
        who = TP;
    }
    write("You cut the oak tree.\n");
    //TODO: compose it
    say(TP->query_name() + " cuts the oak.\n");
    who->give_exp("lumbering", query_exp_reward());
    ::event_gather(who);
}