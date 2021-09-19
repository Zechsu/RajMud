#include <globals.h>

inherit M_DESC;

private nosave string* ids;

void create() {
    if (!sizeof(ids)) {
        ids = ({});
    }
}

 int set_ids(string* new_ids) {
     ids = new_ids;
     return 1;
 }

string* query_ids() {
    return ids;
}

void move(mixed dest) {
    move_object(dest);
}
