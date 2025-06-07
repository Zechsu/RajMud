#include <lib.h>
#include <daemons.h>

inherit LIB_ITEM;

private int folded = 0;

void create() {
    ::create();
    set_short("folding chair");
    set_long("Convienient to carry around and might be useful for fishing.");
    set_ids(({"folding chair", "chair"}));
}

string query_short() {
    string ret = "folding chair";
    if (folded)
        ret += " (folded)";
    else
        ret += " (unfolded)";
    return ret;
}

void init() {
    add_action("do_fold", "fold");
    add_action("do_unfold", "unfold");
}

int do_fold(string arg) {
    object ob;
    if (!arg || trim(arg) == "") {
        return 0;
    }
    if (ob = present(arg, this_player())) {
        string* mess = compose_message(this_player(), "$N $vfold the folding chair.\n");
        tell_object(this_player(), mess[0]);
        tell_object(environment(this_player()), mess[1], ({this_player()}));
        folded = 1;
    }
    return 1;
}

int do_unfold(string arg) {
    object ob;
    if (!arg || trim(arg) == "") {
        return 0;
    }
    if (ob = present(arg, this_player())) {
        string* mess = compose_message(this_player(), "$N $vunfold the folding chair.\n");
        tell_object(this_player(), mess[0]);
        tell_object(environment(this_player()), mess[1], ({this_player()}));
        folded = 0;
    }
    return 1;
}