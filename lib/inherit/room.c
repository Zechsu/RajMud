#include <globals.h>

inherit M_DESC;
inherit M_EXITS;

void create() {

}

void add_item(mixed item) {
    item->move(this_object());
    return;
}

void add_prop(string prop, string desc) {
    object ob = new(LIB_PROP);
    ob->set_id(prop);
    ob->set_long(desc);
    ob->move(this_object());
}

object* query_props() {
    return filter_array(all_inventory(this_object()), (: $1->is_prop() :));
}

object* query_items() {
    object* ret = all_inventory(this_object());
    ret = filter_array(ret, (: !living($1) :));
    ret = filter_array(ret, (: !$1->is_prop() :));
    return ret;
}

int can_enter(object who) {
    return 1;
}

int event_enter(object who) {
    if (can_enter(who)) {
        return 1;
    }
    return 0;
}