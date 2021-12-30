private nosave mapping search_table;
private nosave int empty;
private nosave int cooldown_time;

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
    if (!who) {
        who = this_player();
    }
    if (empty) {
        return "Someone has already searched here, try again later.\n";
    }
    result = element_of_weighted(search_table);
    if (cooldown_time != 0) {
        empty = cooldown_time;
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
    empty--;
    if (empty == 0) {
        set_heart_beat(0);
    }
}
