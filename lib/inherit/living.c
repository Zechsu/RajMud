#include <lib.h>
#include <modules.h>

inherit BASE;
inherit LIB_RACE;
inherit LIB_POSITION;
inherit M_DESC;
inherit M_SKILLS;
inherit M_TRAITS;
inherit M_TITLE;
inherit M_INVENTORY;

private string name;
private string current_room;
private nosave int busy = 0;

void create() {
    ::create();
    position::create();
    if (!current_room) {
        current_room = TEST_ROOM;
    }
}

void set_name(string n) {
    name = n;
    set_ids(({n, lower_case(n)}));
}

string query_name() {
    return name;
}

string query_short() {
    string title = query_title();
    if (title) {
        return sprintf("%s, %s", name, title);
    }
    else {
        return name;
    }
}

string query_long() {
    return sprintf("%s is nondescript.", name);
}

int is_living() {
    return 1;
}

varargs int event_move(mixed dest, int flag) {
    if (!busy) {
        ::move(dest);
        if (!flag) {
            current_room = dest;
        }
        return 1;
    }
    return 0;
}

string query_current_room() {
    return current_room;
}

int force_me(string cmd) {
    return command(cmd);
}

varargs void set_busy(int arg) {
    if (!arg) {
        busy = 1;
    }
    else {
        busy = 0;
    }
}