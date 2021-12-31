#include <globals.h>

inherit BASE;
inherit M_DESC;
inherit M_VISIBLE;

private string drop;
private int drop_amount;
private string action;
private int exp_reward;

void create() {
    ::create();
    if (!drop_amount) {
        drop_amount = 1;
    }
}

int is_gatherable() {
    return 1;
}

// Sets which item will drop after node is gathered
void set_drop(string ob) {
    drop = ob;
}

string query_drop() {
    return drop;
}

// Sets the drop_amount of items that will drop after node is gathered
void set_drop_amount(int i) {
    if (i < 0) {
        drop_amount = 1;
    }
    else {
        drop_amount = i;
    }
}

mixed event_gather(object who) {
    object ob = new(drop, drop_amount);
    ob->event_get(who);
    remove();
    return 1;
}

// Sets the action/required command to gather the node
void set_action(string str) {
    action = str;
}

string query_action() {
    return action;
}

// Sets exp given on action
void set_exp(int exp) {
    exp_reward = exp;
}

int query_exp_reward() {
    return exp_reward;
}

// Since it doesn't inherit item, we make this to stop it from responding with a "What?" when trying to get it
varargs mixed event_get(object who) {
    write("You can't get that.\n");
    return 1;
}