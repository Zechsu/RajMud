/**
 * @file m_search.c
 * @author Rajo (zechsnox@gmail.com)
 * @brief Used for searching in rooms
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

private nosave mapping search_table;
private nosave int empty;
private nosave int cooldown_time;
private nosave mapping players_searched = ([]);

/**
 * @brief Set the search table
 * 
 * @param table Table mapping
 */
void set_search_table(mapping table) {
    search_table = table;
}

/**
 * @brief Set the amount of time it takes to be able to search again
 * 
 * @param t Time in seconds, if `t` is 0 then it will have no cooldown
 */
void set_search_cooldown(int t) {
    cooldown_time = t;
}

/**
 * @brief Living searched
 * 
 * @param who Living
 * @return mixed 
 */
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

/**
 * @brief Handles the cooldowns for searching
 * 
 */
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
