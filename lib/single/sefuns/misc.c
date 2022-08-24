#include <globals.h>
#include <lpctypes.h>
#include <positions.h>
#include "colors.h"

#define ENDS_WITH_Y ({ "enjoy", "toy", "employ", "deploy" })

// returns a white ansi color for resetting colors
// defined in sefuns.c
string white();

mixed* decompose(mixed* org) {
    int i = 0, j;

    if (!arrayp(org)) error("Bad arg type to decompose");
    org = copy(org);

    while (i < sizeof(org)) {
        if (arrayp(org[i])) {
            j = sizeof(org[i]);
            org[i..i] = org[i];
            i += j;
        } else {
            i++;
        }
    }

    return org;
}

/**
 * NAME: sum
 * SYNOPSIS: (int|float) sum( int|float num1, int|float num2, int|float numx... )
 * DESCRIPTION: Returns the sum of all passed values.
 */

mixed sum(mixed *numbers...)
{
    mixed number, result = 0;

    foreach(number in numbers)
    {
        switch(typeof(number))
        {
        case INT :
            result += number ;
            break ;
        case FLOAT :
            result = to_float(result) + number ;
            break ;
        default:
            error("Argument must be an array of int or float.\n");
        }

    }

    return result;
}

/**
 * NAME: array_sum
 * SYNOPSIS: (int|float) array_sum( array int|array float numbers  )
 * DESCRIPTION: Returns the sum of all values in the passed array.
 */

mixed array_sum(mixed *numbers)
{
    return sum(numbers...) ;
}


/**
 * NAME: element_of_weighted
 * SYNOPSIS: mixed element_of_weighted( mapping data )
 * DESCRIPTION: Returns a property from a mapping weighted by its value.
 * The higher the weight (value), the more likely it will be returned.
 * EXAMPLE: element_of_weighted( ([ "element1" : 10, "element2" : 5 ]) )
 * Return value will more likely be "element1" due to its higher weight.
 * DEPENDENCIES: sum
 */

mixed element_of_weighted(mapping data)
{
    int roll_result, next_position, weight, max_weight;
    mixed *elems = ({ }), elem;
    int *weights = ({ }), *indices = ({ }), index = 0;

    foreach(elem, weight in data)
    {
        elems   = ({ elems..., elem });
        weights = ({ weights..., weight });
        indices = ({ indices..., index++ });
    }

    indices       = shuffle(indices);
    next_position = 0;
    max_weight    = OVERRIDES_FILE->sum(weights...);
    roll_result   = random(max_weight);

    foreach(index in indices)
    {
        //get that element's weight
        weight = weights[index];

        //our next_position is the point at which our next element
        //will be available.
        next_position += weight;

        //if our random number (roll_result) falls before our next_position
        //then that's our guy.
        if(roll_result < next_position) return elems[index];
    }
}

// Will return a rainbow colored version of the string
string make_rainbow(string sh) {
    string str = "";
    for (int i = 0; i < sizeof(sh); i++) {
        // RAINBOW_ARR defined in "include/colors.h" has 7 elements
        str += RAINBOW_ARR[i % 7] + sh[i..i];
    }
    return str + white();
}

varargs string alternate_colors(string str, string* colors, int step) {
    string ret = "";
    int current_step = 0, spaces = 0;
    str = trim(str);
    if (!colors) {
        return str;
    }
    if (!step) {
        step = 1;
    }
    for (int i = 0; i < sizeof(str); i++) {
        ret += colors[current_step % sizeof(colors)] + str[i..i];
        if ((i+1-spaces) % step == 0) {
            current_step++;
        }
        if (str[i..i] == " ") {
            spaces += 1;
        }
    }
    return ret += white();
}

string remove_color(string str) {
    return TERM_D->parse_pinkfish(str, 1);
}

string query_position_string(object who) {
    string name = who->query_short();
    int position = who->query_position();
    switch (position) {
    case STANDING:
        return sprintf("%s is standing here.", name);
    case FLYING:
        return sprintf("%s is flying here.", name);
    case SITTING:
        return sprintf("%s is sitting here.", name);
    case CRAWLING:
        return sprintf("%s is crawling here.", name);
    default:
        return sprintf("%s is here.", name);
    }
    return 0;
}

string query_nth(int num) {
    switch (num) {
    case 1:
        return num + "st";
    case 2:
        return num + "nd";
    case 3:
        return num + "rd";
    default:
        return num + "th";
    }
}

varargs string invert_cardinal_direction(string dir, int flag) {
    switch (lower_case(dir)) {
    case "north":
        return "south";
    case "west":
        return "east";
    case "south":
        return "north";
    case "east":
        return "west";
    case "in":
        return flag? "outside" : "out";
    case "out":
        return flag? "inside" : "in";
    default:
        return "undefined";
    }
}

// Returns an list formatted like "string1, string2, string3 and string4"
// Stolen from gesslar <3
varargs string list_strings(string* list, string conjunction) {
    int sz;

    if(nullp(list)) error("Missing argument 1 to list_strings.\n");
    if(stringp(list)) list = ({ list });
    if(pointerp(list)) list = filter(list, (: stringp :));
    else error("Invalid argument 1 to list_strings.\n");

    if(!conjunction) conjunction = "and";

    sz = sizeof(list);
    switch(sz)
    {
        case 0 : return "";
        case 1 : return list[0];
        case 2 : return sprintf("%s %s %s", list[0], conjunction, list[1]);
        default:
            list[sizeof(list) - 1] = conjunction + " " + list[sizeof(list) - 1];
            return implode(list, ", ");
    }

    return "";
}

string capitalize_colored(string str) {
    string rmv = remove_color(str);
    int idx = strsrch(str, rmv[0]);
    str[idx..idx] = capitalize(str[idx..idx]);
    return str;
}

int percent(int num, int den) {
    if( floatp(num)  || floatp( den ) ) return num * 100.0 / den;
    else return num * 100 / den;
}

int percent_of(int percent, int base) {
    if( floatp(percent) || floatp( base ) ) return percent * base / 100.0;
    else return percent * base / 100;
}

// Stolen from gurbalib <3
varargs string *compose_message(object who, string msg, object target, mixed * objs) {
    string *words, us, them, others;
    int punc, i, objnum, pronounFlag;

    us = "";
    them = "";
    others = "";

    if (msg && msg != "") {
        words = explode(msg, " ");
    } else {
        return (({ us, them, others }));
    }

    for (i = 0; i < sizeof(words); i++) {
        if (words[i] == "") {;
            continue;
        }

        if (words[i][0] == '$' && strlen(words[i]) >= 2) {

            if (words[i][strlen(words[i]) - 1] == '.' ||
              words[i][strlen(words[i]) - 1] == ',' ||
              words[i][strlen(words[i]) - 1] == '!' ||
              words[i][strlen(words[i]) - 1] == '?') {

                punc = words[i][strlen(words[i]) - 1];
                words[i] = words[i][0..strlen(words[i]) - 2];
            } else {
                punc = 0;
            }
            if (pronounFlag == 1 && words[i][1] != 'o') {
                pronounFlag = 0;
            }
            switch (words[i][1]) {
            case 'N':
                if (who->is_living()) {
                    if (!who->query_name()) {
                        us += "you ";
                        them += "the " + who->query_id() + " ";
                        others += "the " + who->query_id() + " ";
                    } else {
                        us += "you ";
                        them += who->query_name() + " ";
                        others += who->query_name() + " ";
                    }
                } else {
                    us += "you ";
                    them += "the " + who->query_id() + " ";
                    others += "the " + who->query_id() + " ";
                }

                break;
            case 'n':
                us += "you ";
                them += who->query_pronoun() + " ";
                others += who->query_pronoun() + " ";
                break;
            case 'p':
                us += "your ";
                them += who->query_possessive_determiner() + " ";
                others += who->query_possessive_determiner() + " ";
                pronounFlag = 1;
                break;
            case 'P': /* capital P */
                us += "your ";
                them += who->query_determiner()  + " ";
                others += who->query_determiner()  + " ";
                pronounFlag = 1;
                break;
            case 'v':
                if (strlen(words[i]) < 3) {
                    break;
                }

                us += words[i][2..] + " ";

                if (words[i][2..] == "are") {
                    them += "is ";
                    others += "is ";
                } else if (words[i][2..] == "say:") {
                    them += "says: ";
                    others += "says: ";
                } else if (words[i][2..] == "ask:") {
                    them += "asks: ";
                    others += "asks: ";
                } else if (words[i][2..] == "remark:") {
                    them += "remarks: ";
                    others += "remarks: ";
                } else if (words[i][2..] == "mumble:") {
                    them += "mumble: ";
                    others += "mumbles: ";
                } else if (words[i][2..] == "shout:") {
                    them += "shouts: ";
                    others += "shouts: ";
                } else if (words[i][2..] == "ponder:") {
                    them += "ponders: ";
                    others += "ponders: ";
                } else if (words[i][2..] == "whisper:") {
                    them += "whispers: ";
                    others += "whispers: ";
                } else if (words[i][2..] == "exclaim:") {
                    them += "exclaims: ";
                    others += "exclaims: ";
                } else if (words[i][2..] == "mutter:") {
                    them += "mutters: ";
                    others += "mutters: ";
                } else if (words[i][2..] == "say") {
                    them += "says ";
                    others += "says ";
                } else if (words[i][strlen(words[i]) - 1] == 'o') {
                    them += words[i][2..] + "es ";
                    others += words[i][2..] + "es ";
                } else if (words[i][strlen(words[i]) - 1] == 'h' &&
                  words[i][strlen(words[i]) - 2] != 'g') {
                    them += words[i][2..] + "es ";
                    others += words[i][2..] + "es ";
                } else if (words[i][strlen(words[i]) - 1] == 'y') {
                    if (member_array(words[i][2..], ENDS_WITH_Y) == -1) {
                        them += words[i][2..strlen(words[i]) - 2] + "ies ";
                        others += words[i][2..strlen(words[i]) - 2] + "ies ";
                    } else {
                        them += words[i][2..] + "s ";
                        others += words[i][2..] + "s ";
                    }
                } else if (words[i][strlen(words[i]) - 1] == 's') {
                    them += words[i][2..] + "es ";
                    others += words[i][2..] + "es ";
                } else {
                    them += words[i][2..] + "s ";
                    others += words[i][2..] + "s ";
                }
                break;
            case 'T':
                if (who == target) {
                    /* Doing something to ourselves. */
                    us += "yourself ";
                    them += who->query_reflexive() + " ";
                    others += who->query_reflexive() + " ";
                } else {
                    if (target->is_living()) {
                        if (!target->query_name()) {
                            us += "the " + target->query_id() + " ";
                            them += "you ";
                            others += "the " + target->query_id() + " ";
                        } else {
                            us += target->query_name() + " ";
                            them += "you ";
                            others += target->query_name() + " ";
                        }
                    } else {
                        us += "the " + target->query_short() + " ";
                        them += "you " + target->query_short() + " ";
                        others += "the " + target->query_short() + " ";
                    }
                }
                break;
            case 't':
                if (who == target) {
                    /* Doing something to ourselves. */
                    us += "yourself ";
                    them += who->query_reflexive() + " ";
                    others += who->query_reflexive() + " ";
                } else {
                    if (target->is_living()) {
                        if (!target->query_name()) {
                            us += "the " + target->query_id() + " ";
                            them += "you ";
                            others += "the " + target->query_id() + " ";
                        } else {
                            us += target->query_name() + " ";
                            them += "you ";
                            others += target->query_name() + " ";
                        }
                    } else {
                        us += "the " + target->query_short() + " ";
                        them += "you " + target->query_short() + " ";
                        others += "the " + target->query_short() + " ";
                    }
                }
                break;
            case 'o':
                if (strlen(words[i]) > 2 && words[i][2] >= '0'
                  && words[i][2] <= '9') {
                    objnum = words[i][2] - '0';
                } else {
                    objnum = 0;
                }
                if (!objs || !objs[objnum]) {
                    break;
                }
                if (typeof(objs[objnum]) == STRING) {
                    us += objs[objnum] + " ";
                    them += objs[objnum] + " ";
                    others += objs[objnum] + " ";
                } else {
                    if (!pronounFlag) { 
                        us += "the ";
                        them += "the ";
                        others += "the ";
                    }

                    us += objs[objnum]->query_id() + " ";
                    them += objs[objnum]->query_id() + " ";
                    others += objs[objnum]->query_id() + " ";
                    pronounFlag = 0;
                }
                break;
            }

            if (punc) {
                us[strlen(us) - 1] = punc;
                them[strlen(them) - 1] = punc;
                others[strlen(others) - 1] = punc;
                us += " ";
                them += " ";
                others += " ";
            }
        } else {
            us += words[i] + " ";
            them += words[i] + " ";
            others += words[i] + " ";
        }
    }
    if (us[strlen(us) - 1] == ' ') {
        /* We need to strip the final space. */
        us = us[0..strlen(us) - 2];
        them = them[0..strlen(them) - 2];
        others = others[0..strlen(others) - 2];
    }

    return (( { us, them, others } ));
}

// append and prepend stolen from gesslar
// Append suffix to main if it is missing
string append(string main, string suffix)
{
    int len = sizeof(main) ;
    int sufflen = sizeof(suffix) ;

    if(sufflen > len) return main + suffix ;
    if(main[ <sufflen.. ] == suffix) return main ;

    return main + suffix ;
}

// Prepend prefix to main if it is missing
string prepend(string main, string prefix)
{
    int len = sizeof(main) ;
    int preflen = sizeof(prefix) ;

    if(preflen > len) return prefix + main ;
    if(main[0..preflen-1] == prefix) return main ;
    
    return prefix + main ;
}