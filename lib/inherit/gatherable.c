#include <globals.h>

inherit BASE;
inherit M_DESC;
inherit M_VISIBLE;

private string drop;
private int drop_amount;
private string action;
private int exp_reward;
private string* skills;

void create() {
    ::create();
    m_visible::create();
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

void set_skills(string* s) {
    skills = s;
}

string* query_skills() {
    return skills;
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

int query_drop_amount() {
    return drop_amount;
}

void get_drop(object who) {
    object ob = new(drop);
    ob->add_weight(query_drop_amount());
    ob->event_get(who);
}

int can_gather(object who) {
    if (!who) {
        who = this_player();
    }
    return 1;
}

mixed event_gather(object who) {
    Log("BUG", "Gatherable without event_gather()!  " + this_object());
    return 0;
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
