#include <globals.h>
#include <lpctypes.h>

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