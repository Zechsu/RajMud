#include <globals.h>
#include <lpctypes.h>
#include "colors.h"

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

string remove_color(string str) {
    return TERM_D->parse_pinkfish(str, 1);
}