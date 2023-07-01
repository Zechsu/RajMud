#include <lib.h>

inherit LIB_ITEM;

private string monster_path;
void set_monster_path(string path);

void create() {
    ::create();
}

void init() {
    add_action("do_use", "use");
}

void set_monster_path(string path) {
    object mon;
    monster_path = path;
    mon = new(path);
    set_short(mon->query_short() + " spawn egg");
    set_long("Syntax: use egg to spawn a " + mon->query_short());
    set_ids(({"spawn egg", "egg", mon->query_short() + " egg", mon->query_short() + " spawn egg"}));
}

string query_monster_path() {
    return monster_path;
}

int do_use(string arg) {
    object mon;
    if (!arg || trim(arg) == "")
        return 0;
    if (!id(arg)) {
        return 0;
    }
    if (!monster_path) {
        debug_message("Spawn egg without monster path!\n");
        return 0;
    }
    mon = new(monster_path);
    mon->move(environment(this_player()));
    this_object()->remove();
    tell_room(environment(this_player()), "Bruh a " + mon->query_short() + " just spawned\n");
    return 1;
}

int is_spawn_egg() {
    return 1;
}