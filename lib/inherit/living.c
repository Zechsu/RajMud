#include <lib.h>
#include <modules.h>

inherit BASE;
inherit LIB_RACE;
inherit LIB_POSITION;
inherit LIB_COMMAND;
inherit M_DESC;
inherit M_SKILLS;
inherit M_TRAITS;
inherit M_TITLE;
inherit M_INVENTORY;

private string name;
private string current_room;
private nosave int busy = 0;

void create() {
    race::create();
    position::create();
    enable_commands();
    if (!current_room) {
        current_room = TEST_ROOM;
    }
}

void setup() {
    command::setup();
}

void set_name(string n) {
    name = n;
    set_ids(({n, lower_case(n)}));
    set_living_name(name);
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
    // <PRONOUN> is a <RACE>
    string ret = sprintf("%s is a %s. ", capitalize(query_pronoun()), query_race());
    object* worn = query_worn();
    if (sizeof(worn)) {
        ret += sprintf("%s is equipped with ", capitalize(query_pronoun()));
        foreach (object w in worn) {
            ret += sprintf("\n%-30s %-30s", w->query_short(), w->worn_attributes());
        }
    }
    return ret;
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
