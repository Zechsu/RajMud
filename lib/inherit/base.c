#include <modules.h>
#include "modules/include/m_hooks.h"

inherit M_HOOKS;

private nosave string* adjectives;

// set to 'private static' so that inheritor won't be able to directly
// access this variable and so that save_object() won't save it to the .o file

private nosave string *ids;

void
remove()
{
    // add code here to prevent unwanted destructions.
    // update attributes of the container and the containees.
    if (clonep(this_object())) {
        destruct(this_object());
    }
}

int move(mixed dest)
{
    // add code here to prevent disallowed moves (target is full, object
    // is immovable, etc.).
    if (dest == this_object()) {
        return notify_fail("You can't move an object inside itself!.\n");
    }
    call_hook("move", HOOK_IGNORE);
    move_object(dest);
    return 1;
}

void
set_ids(string *arg)
{
    // probably want to add some security here.
    ids = arg;
}

int id(string arg)
{
    if (!arg || !ids) {
        return 0;
    }
    if (adjectives) {
        foreach (string adj in adjectives) {
            foreach (string id in ids) {
                if (arg == adj + " " + id) {
                    return 1;
                }
            }
        }
    }
    return (member_array(arg, ids) != -1);
    // return 0;
}

string* query_ids() {
    return ids;
}

void set_adjectives(string* adjs) {
    adjectives = adjs;
}
