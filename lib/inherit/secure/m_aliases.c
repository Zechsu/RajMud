#include <globals.h>

private mapping aliases = ([]);
private nosave mapping predefined_aliases = (["l":"look", "i":"inventory"]);
nosave mapping dir_aliases = (["n":"go north", "w":"go west", "s":"go south", "e":"go east", "in":"go in", "out":"go out"]);

void create() {
    if (!sizeof(aliases)) {
        aliases = ([]);
    }
}

mapping query_aliases() {
    return aliases;
}

mapping query_predefined_aliases() {
    return predefined_aliases;
}

int add_alias(string alias, string command) {
    aliases[alias] = command;
    return 1;
}

int remove_alias(string alias) {
    if (aliases[alias]) {
        map_delete(aliases, alias);
        return 1;
    }
    return 0;
}

string get_alias(string alias) {
    if (aliases[alias]) {
        return aliases[alias];
    }
    else if (predefined_aliases[alias]) {
        return predefined_aliases[alias];
    }
    return alias;
}

int is_dir_alias(string alias) {
    if (dir_aliases[alias]) {
        return 1;
    }
    else {
        return 0;
    }
}