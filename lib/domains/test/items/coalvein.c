#include <globals.h>

inherit LIB_GATHERABLE;

void create() {
    ::create();
    set_short("%#949494%#coal vein%^RESET%^");
    set_long("It's a vein of coal. You could mine some.");
    set_ids(({"coal vein", "coal", "vein"}));
    set_action("mine");
    set_drop("/domains/test/items/coal");
    set_exp(1);
}

mixed event_gather(object who) {
    if (!who) {
        who = TP;
    }
    write("You mine the coal vein.\n");
    say(TP->query_name() + " mines the coal vein.\n");
    who->give_exp("mining", query_exp_reward());
    ::event_gather(who);
}