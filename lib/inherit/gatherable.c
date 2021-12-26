#include <globals.h>

inherit BASE;
inherit M_DESC;

private string drop;
private int drop_amount;
private string action;

void create() {
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
    debug_message("event_gather() not set for " + ENV(TO));
    return 0;
} 

// Sets the action/required command to gather the node
void set_action(string str) {
    action = str;
}

string query_action() {
    return action;
}