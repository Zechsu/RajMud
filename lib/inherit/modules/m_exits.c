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
 * @brief Adds a door to this room\n
 * This is called by the door object
 * 
 * @param side On which exit is the door
 * @param door Object of the door
 * @param destination Where the door leads
 * @return int Returns 1 if added
 */
int add_door(string side, object door, string destination) {
    // If not given a destination try to add it to an existing side
    if (!destination) {
        // If side already exists, add a door to it
        if (exits[side]) {
            exits[side] = (["destination":exits[side], "door":door]);
            return 1;
        }
        debug_message("Side does not exist\n");
        return 0;
    }
    // If given a destination, maka a new side
    else {
        exits[side] = (["destination":destination, "door":door]);
        return 1;
    }
}

/**
 * @brief Checks if exit has a door
 * 
 * @param side Direction of exit
 * @return int Returns 1 if it's a door
 */
int is_door(string side) {
    if (mapp(exits[side])) {
        return 1;
    }
    else {
        return 0;
    }
}

/**
 * @brief Returns the door object of an exit
 * 
 * @param dir Direction of the exit
 * @return object Door object
 */
object query_door(string dir) {
    if (exits[dir]["door"]) {
        return exits[dir]["door"];
    }
}

/**
 * @brief Returns where an exit leads to
 * 
 * @param dir Direction of the exit
 * @return string Location of the room file
 */
string query_destination(string dir) {
    if (exits[dir]["destination"]) {
        return exits[dir]["destination"];
    }
}