#include "include/m_hooks.h"
#include <function.h>

private nosave mapping hooks = ([]);

void add_hook(string tag, function hook) {
    mixed* tmp = ({hook});
    // Make sure we have only 1 hook
    if (hooks[tag]) {
        hooks[tag] -= tmp;
        hooks[tag] += tmp;
    } else {
        hooks[tag] = tmp;
    }
}

void remove_hook(string tag, function hook) {
    if (hooks[tag]) {
        hooks[tag] -= ({hook});
    }
    if (!sizeof(hooks[tag])) {
        map_delete(hooks, tag);
    }
}

void hook_state(string tag, function hook, int state) {
    if (state) add_hook(tag, hook);
    else remove_hook(tag, hook);
}

varargs mixed call_hook(string tag, mixed func, mixed start, mixed* args...) {
    mixed* hooks_to_call = hooks[tag];

    if (!hooks_to_call) {
        return 0;
    }

    if (!intp(func)) {
        return 0;
    }
    switch (func) {
        case HOOK_IGNORE: {
            map_array(hooks_to_call, (:evaluate($1, $(args)...):));
            return 0;
        }
    }
}

mapping debug_hooks() {
  return copy(hooks);
}