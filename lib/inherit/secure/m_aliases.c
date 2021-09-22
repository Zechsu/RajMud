#include <globals.h>

private mapping aliases = ([]);
private nosave mapping predefined_aliases = (["n":"go north", "w":"go west", "s":"go south", "e":"go east", "l":"look", "i":"inventory", "in":"go in", "out":"go out"]);

void create() {
    if (!sizeof(aliases)) {
        aliases = ([]);
    }
}

mapping query_aliases() {
    return aliases;
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