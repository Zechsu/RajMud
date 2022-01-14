#include <globals.h>
#include <lpctypes.h>

mixed *distinct_array(mixed *arr) {
    mapping tmp;
    int i, maxi;

    for(i = 0, tmp = allocate_mapping(maxi = sizeof(arr)); i<maxi; i++){
        tmp[arr[i]] = 1;
    }
    return keys(tmp);
}