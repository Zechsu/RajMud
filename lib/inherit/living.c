#include <globals.h>

inherit BASE;
inherit LIB_RACE;
inherit M_DESC;
inherit M_SKILLS;
inherit M_TRAITS;

private string name;
private string current_room;

void create() {
    ::create();
     if (!current_room) {
          current_room = TEST_ROOM;
     }
}

void set_name(string n) {
    name = n;
    set_ids(({n}));
}

string query_name() {
    return name;
}

string query_long() {
     return sprintf("%s is nondescript.", name);
}

int is_living() {
    return 1;
}

varargs int move(mixed dest, int flag) {
     ::move(dest);
     if (!flag) {
          current_room = dest;
     }
}

string query_current_room() {
     return current_room;
}

int force_me(string cmd) {
    return command(cmd);
}
