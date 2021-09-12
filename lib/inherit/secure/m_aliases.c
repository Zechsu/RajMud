#include <globals.h>

private mapping aliases = ([]);

mapping query_aliases() {
    return aliases;
}

void add_alias(string alias, string command) {
    aliases[alias] = command;
}

void remove_alias(string alias) {
    if (aliases[alias]) {
        map_delete(aliases, alias);
    }
}

string get_alias(string alias) {
    if (aliases[alias]) {
        return aliases[alias];
    }
    return alias;
}