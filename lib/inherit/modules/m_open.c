/**
 * @file m_open.c
 * @author Rajo (zechsnox@gmail.com)
 * @brief Used for objects that can be opened and closed
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "include/m_description.h"

private int opened;
private int can_open;
private int can_close;

/**
 * @brief Checks if object is opened
 * 
 * @return int 
 */
int is_open() {
    return opened;
}

/**
 * @brief Toggles between object being opened and closed
 * 
 */
void toggle_opened() {
    opened = !opened;
}

/**
 * @brief Hard set if the object can be opened
 * 
 * @param i Number above 0 
 */
void set_can_open(int i) {
    if (!i) {
        can_open = 0;
    }
    else {
        can_open = 1;
    }
}

/**
 * @brief Hard set if the object can be closed
 * 
 * @param i Number above 0
 */
void set_can_close(int i) {
    if (!i) {
        can_close = 0;
    }
    else {
        can_close = 1;
    }
}
/**
 * @brief Checks if object can open. Called at event_open()
 * 
 * @param who Object in question
 * @return int 
 */
varargs int can_open(object who) {
    if (!who) {
        who = this_player();
    }
    if (!can_open) {
        return notify_fail("You can't open that.\n");
    }
    if (opened) {
        return notify_fail("It is opened already.\n");
    }
    return 1;
}

/**
 * @brief Checks if object can close. Called at event_close()
 * 
 * @param who Object in question
 * @return int 
 */
varargs int can_close(object who) {
    if (!who) {
        who = this_player();
    }
    if (!can_close) {
        return notify_fail("You can't close that.\n");
    }
    if (!opened) {
        return notify_fail("It is closed already.\n");
    }
    return 1;
}
/**
 * @brief Opens the object
 * 
 * @param who Object who opened
 * @return mixed 
 */
varargs mixed event_open(object who) {
    if (!can_open()) {
        return 0;
    }
    write("You open " + TO->query_short() + ".\n");
    opened = 1;
    return 1;
}

/**
 * @brief Closes the object
 * 
 * @param who Object who closed
 * @return int 
 */
varargs mixed event_close(object who) {
    if (!can_close()) {
        return 0;
    }
    write("You close " + TO->query_short() + ".\n");
    opened = 0;
    return 1;
}
