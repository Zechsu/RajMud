/**
 * @file m_description.c
 * @author Rajo (zechsnox@gmail.com)
 * @brief Used for objects that have descriptions
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
private string short_desc;
private string long_desc;

/**
 * @brief Set the short description
 * 
 * @param new_short New short description
 */
void set_short(string new_short) {
    short_desc = new_short;
}

/**
 * @brief Set the long description
 * 
 * @param new_long New long description
 */
void set_long(string new_long) {
    long_desc = new_long;
}

/**
 * @brief Returns the short description
 * 
 * @return string Short description
 */
string query_short() {
    return short_desc;
}

/**
 * @brief Returns the long description
 * 
 * @return string Long description
 */
string query_long() {
    return long_desc;
}
