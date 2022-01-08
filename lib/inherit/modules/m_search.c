private nosave mapping search_table;
private nosave int empty;
private nosave int cooldown_time;
private nosave mapping players_searched = ([]);

void set_search_table(mapping table) {
    search_table = table;
}

// Sets the amoutn of time it takes for a search where t is in seconds
// When t == 0, no cooldown will be applied
void set_search_cooldown(int t) {
    cooldown_time = t;
}

mixed event_searched(object who) {
    mixed result;
    string name;
    if (!who) {
        who = this_player();
    }
    name = who->query_name();
    if (players_searched[name]) {
        return "You've already searched here, try again later.\n";
    }
    result = element_of_weighted(search_table);
    if (!players_searched[name]) {
        players_searched[name] = cooldown_time;
        set_heart_beat(1);
    }
    if (result != 0) {
        object ob = new(result);
        ob->move(this_player());
        return "You found " + ob->query_short() + "!\n";
    }
    return "You did not find anything interesting.\n";
}

void heart_beat() {
    string* keys = keys(players_searched);
    for (int i = 0; i < sizeof(players_searched); i++) {
        players_searched[keys[i]] -= 1;
        if (players_searched[keys[i]] <= 0) {
            map_delete(players_searched, keys[i]);
        }
    }
    if (!sizeof(players_searched)) {
        set_heart_beat(0);
    }
}

void print_searches() {
    string ret = "";
    foreach (string name, int time in players_searched) {
        ret += sprintf("%-10s %ds\n", name, time);
    }
    write(ret);
}