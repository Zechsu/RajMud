#include <globals.h>

int locked;
int can_lockpick;
int complexity;

int set_can_lockpick(int can);
int set_complexity(int comp);

void create() {
    set_can_lockpick(1);
    set_complexity(0);
}

int set_can_lockpick(int can) {
    can_lockpick = can;
    return 1;
}

int set_locked(int lock) {
    locked = lock;
    return 1;
}

int query_complexity() {
    return complexity;
}

int set_complexity(int comp) {
    complexity = comp;
    return 1;
}

mixed event_pick_lock(object who) {
    if (!who) {
        who = this_player();
    }
    if (!locked) {
        return "It's already unlocked.\n";
    }
    locked = 0;
    return 1;
}

int is_locked() {
    if (locked) {
        return 1;
    }
    return 0;
}

mixed event_lock(object who, object key) {
    if (!key) {
        return "You do not have a key.\n";
    }
    if (!who) {
        who = this_player();
    }
    if (locked) {
        return "It is locked already.\n";
    }
    locked = 1;
    return 1;
}

mixed event_unlock(object who, object key) {
    if (!key) {
        return "You do not have a key.\n";
    }
    if (!who) {
        who = this_player();
    }
    if (!locked) {
        return "It is unlocked already.\n"; 
    }
    locked = 0;
    return 1;
}

int has_lock() {
    return 1;
}
