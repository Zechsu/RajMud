#include <lib.h>
#include <modules.h>
#include <flags/item_flags.h>
#include "include/item.h"

inherit BASE;
inherit M_DESC;
inherit M_VISIBLE;
inherit M_FLAGS;
inherit LIB_PERSIST;

void create() {
    ::create();
    if (!sizeof(query_ids())) {
        set_ids(({}));
    }
}

int move(mixed dest) {
    object* players;
    int res = ::move(dest);
    object env = environment(this_object());

    if (userp(env)) {
        players = all_inventory(environment(env));
    }
    else {
        players = all_inventory(env);
    }
    players = filter_array(players, (: userp($1) :));
    map(players, (: $1->gmcp("Room.Items") :));

    return res;
}

int can_get(object who) {
    string* hands;
    if (!who) {
        who = this_player();
    }
    hands = Race(who->query_race())->query_hands();
    if (query_flag(ITEM_NO_GET)) {
        return notify_fail("You can't get that!\n");
    }
    if (!who->has_limbs(hands)) {
        return notify_fail("You do not have any hands.\n");
    }
    return 1;
}

varargs mixed event_recieved(object who) {
    if (!who) {
        who = this_player();
    }
    return move(who);
}

protected mixed* add_save(mixed* vars) {
    if (!vars) vars = ({});
    return persist::add_save(vars);
}

string* query_save() {
    return persist::query_csaved();
}

varargs mixed event_get(object who) {
    if (!who) {
        who = TP;
    }
    if (!can_get(who)) {
        return 0;
    }
    write("You get " + query_short() + ".\n");
    say(who->query_name() + " gets " + query_short() + "\n");
    event_recieved(who);
    return 1;
}

varargs mixed event_get_from(object who, object where) {
    if (!who) {
        who = TP;
    }
    if (!can_get(who)) {
        return notify_fail("You can't get that.\n");
    }
    write("You get " + query_short() + " from " + where->query_short() + ".\n");
    say(who->query_name() + " gets " + query_short() + " from " + where->query_short() + "\n");
    event_recieved(who);
    return 1;
}

int can_drop(object who) {
    return 1;
}

varargs mixed event_drop(object who) {
    if (!who) {
        who = TP;
    }
    if (!can_drop(who)) {
        return 0;
    }
    tell_object(who, "You drop " + query_short() + ".\n");
    tell_room(environment(who), who->query_name() + " drops " + query_short() + "\n", ({who}));

    return move(environment(who));
}

int is_item() {
    return 1;
}
