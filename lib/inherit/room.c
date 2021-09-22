#include <globals.h>

inherit M_DESC;
inherit M_EXITS;
inherit CLEAN_UP;

void create() {

}

void add_item(mixed item) {
    item->move(this_object());
    return;
}

void add_prop(string prop, string desc) {
    object ob = new(LIB_PROP);
    ob->set_id(prop);
    ob->set_description(desc);
    ob->move(this_object());
}