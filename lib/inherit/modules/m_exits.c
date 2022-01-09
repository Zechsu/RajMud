/**
 * @file m_exits.c
 * @author Rajo (zechsnox@gmail.com)
 * @brief Used for exits in rooms
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
private mapping exits = ([]);

/**
 * @brief Adds an exit
 * 
 * @param direction
 * @param destination Location of room file
 * @return void
 */
void add_exit(string direction, string destination) {
    if (!exits[direction]) {
        exits[direction] = destination;
    }
}
/**
 * @brief Set the exits
 * 
 * @param new_exits Mapping of exits
 */
void set_exits(mapping new_exits) {
    exits = new_exits;
}

void set_exit(string direction, mixed dest) {
    exits[direction] = dest;
}

/**
 * @brief Removes an exit
 * 
 * @param exit Exit to be removed
 */
void remove_exit(string exit) {
    if (exits[exit]) {
        map_delete(exits, exit);
    }
}

/**
 * @brief Returns exits mapping
 * 
 * @return mapping Exits
 */
mapping query_exits() {
    return copy(exits);
}

/**
 * @brief Returns exits keys (their direction)
 * 
 * @return string* Exits
 */
string* query_exit_keys() {
    return (exits? keys(exits) : 0);
}

/**
 * @brief Returns the door object of an exit
 * 
 * @param dir Direction of the exit
 * @return object Door object
 */
object query_door(string dir) {
    if (objectp(exits[dir])) {
        return exits[dir];
    }
    return 0;
}

/**
 * @brief Returns where an exit leads to
 * 
 * @param dir Direction of the exit
 * @return string Location of the room file
 */
string query_destination(string dir) {
    if (exits[dir]) {
        return exits[dir];
    }
}