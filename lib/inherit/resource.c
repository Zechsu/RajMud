#include <lib.h>

inherit LIB_ITEM;

int stack();

private mixed weight = 0;
private string resource = "";

void create() {
    ::create();
    add_save(({"weight", "short_desc", "ids", "resource"}));
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
    return res + "\nIt weighs "  + weight + "grams.";
}

string query_short() {
    string res = ::query_short();
    return weight + "grams of " + res;
}

int move(mixed dest)
{
    if (!stack()) {
        return ::move(dest);
    }
    return 1;
}

int stack() {
    object who = this_interactive();
    object stack;
    stack = present(resource, who);
    if (stack) {
        stack->add_weight(weight);
        this_object()->remove();
        return 1;
    }
    return 0;
}