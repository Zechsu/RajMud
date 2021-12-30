#include <globals.h>

inherit LIB_ITEM;

private mixed weight = 0;
private string resource = "";

void create() {
    ::create();
    add_save(({"weight"}));
}

void add_weight(int amt) {
    weight += amt;
}

mixed query_weight() {
    return weight;
}

void set_resource(string res) {
    resource = res;
}

string query_resource() {
    return resource;
}

string query_long() {
    string res = ::query_long();
    return res + "\nIt weighs "  + weight + "kgs.";
}

string query_short() {
    string res = ::query_short();
    return weight + "kgs of " + res;
}

varargs mixed event_get(object who) {
    object stack;
    if (!who) {
        who = TP;
    }
    
    stack = present(resource, who);

    if (stack) {
        stack->add_weight(weight);
        write("You get " + query_short() + "\n");
        remove();
        return 1;
    }
    else {
        return ::event_get(who);
    }
}