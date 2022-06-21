#include <lib.h>
#include <armor_layers.h>

inherit LIB_GATHERABLE;

void create() {
    ::create();
    set_short("coal vein");
    set_long("It's a vein of coal. You could mine some.");
    set_ids(({"coal vein", "coal", "vein"}));
    set_action("mine");
    set_drop("/domains/test/items/coal");
    set_exp(1);
}

int can_gather(object who) {
    object* tools = who->query_wield() + who->query_worn("head", A_TEETH);
    if (!sizeof(filter_array(tools, (: $1->is_mining_tool() :))) > 0) {
        return notify_fail_colored("%^RED%^You lack the tools required.%^RESET%^\n");
    }
    return ::can_gather(who);
}

mixed event_gather(object who) {
    int res;
    if (!who) {
        who = TP;
    }
    res = ::event_gather(who);
    if (res) {
        write("You mine the coal vein.\n");
        //TODO: compose it
        say(TP->query_name() + " mines the vein.\n");
        who->give_exp("mining", query_exp_reward());     
        return 1;
    }
    return 0;
}