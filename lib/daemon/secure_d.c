#include <globals.h>
#include <daemons.h>
#include <security.h>

private mapping users = ([]);
private mapping wizards = ([]);
private mapping builders = ([]);

void create() {
    if (clonep(this_object())) {
        return;
    }
    if (!restore_object(ACCESS_SAVE)) {
        wizards = ([]);
        users = ([]);
        builders = ([]);
    }
}

nomask void make_wizard(string wizard) {
    if (!find_player(wizard)) {
        return;
    }
    if (wizards[wizard]) {
        return;
    }
    wizards[wizard] = 1;
    find_player(wizard)->refresh_search_paths();
    save_object(ACCESS_SAVE);
}

nomask void make_builder(string builder) {
    if (!find_player(builder)) {
        return;
    }
    if (builders[builder]) {
        return;
    }
    builders[builder] = 1;
    find_player(builder)->refresh_search_paths();
    save_object(ACCESS_SAVE);
}

nomask void delete_wizard(string wizard) {
    if (!find_player(wizard)) {
        return;
    }
    if (!wizards[wizard]) {
        return;
    }
    map_delete(wizards, wizard);
    find_player(wizard)->refresh_search_paths();
    save_object(ACCESS_SAVE);
}

nomask void make_user(string user) {
    if (users[user]) {
        return;
    }
    users[user] = 1;
    save_object(ACCESS_SAVE);
}

nomask void delete_user(string user) {
    if (!users[user]) {
        return;
    }
    map_delete(users, user);
    find_player(user)->refresh_search_paths();
    save_object(ACCESS_SAVE);
}

nomask void delete_builder(string builder) {
    if (!builders[builder]) {
        return;
    }
    map_delete(builders, builder);
    find_player(builder)->refresh_search_paths();
    save_object(ACCESS_SAVE);
}

nomask int query_wizard(string wizard) {
    if (wizards[wizard]) {
        return 1;
    }
    return 0;
}

nomask int query_user(string user) {
    if (users[user]) {
        return 1;
    }
    return 0;
}

nomask int query_builder(string builder) {
    if (builders[builder]) {
        return 1;
    }
    return 0;
}

nomask string* query_all_wizards() {
    return keys(wizards);
}

nomask string* query_all_builders() {
    return keys(builders);
}

string* query_search_paths(mixed user) {
    if (stringp(user)) {
        string* ret = ({});
        ret += ({COMMAND_PREFIX});
        if (query_wizard(user)) {
            ret += ({"/command/wizard/"});
        }
        if (query_builder(user)) {
            ret += ({"/command/builder/"});
        }
        return ret;
    }
    return 0;
}