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