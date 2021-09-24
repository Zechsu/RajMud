#include <globals.h>

inherit M_DESC;

private nosave string* ids;
private mapping messages;

void create() {
    if (!sizeof(ids)) {
        ids = ({});
    }
    if (!sizeof(messages)) {
        messages = ([]);
    }
}

 int set_ids(string* new_ids) {
     ids = new_ids;
     return 1;
 }

string* query_ids() {
    return ids;
}

int set_message(string kind, string mess) {
    mess = replace_string(mess, "$N", query_short());
    messages[kind] = mess;
}

string query_message(string kind) {
    if (messages[kind]) {
        return messages[kind];
    }
    else {
        return sprintf("a %s is on the ground.", query_short());
    }
}

void move(mixed dest) {
    move_object(dest);
}
