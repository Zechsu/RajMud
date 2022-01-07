#include <globals.h>

inherit M_DESC;
inherit M_EXITS;

void create() {

}

void add_item(mixed item) {
    item->move(this_object());
    return;
}

void add_prop(string prop, string desc) {
    object ob = new(LIB_PROP);
    ob->set_id(prop);
    ob->set_long(desc);
    ob->move(this_object());
}

object* query_props() {
    return filter_array(all_inventory(this_object()), (: $1->is_prop() :));
}

object* query_items() {
    object* ret = all_inventory(this_object());
    ret = filter_array(ret, (: !living($1) :));
    ret = filter_array(ret, (: !$1->is_prop() :));
    return ret;
}

int can_go(object who) {
    return 1;
}

varargs int event_enter(string direction, object who) {
    int pos;
    mapping exits = query_exits();
    string inverse = invert_cardinal_direction(direction);
    if (!can_go(who)) {
        return 0;
    }
    if (!who) {
        who = this_player();
    }
    pos = who->query_position();
    // You go/Someone goes
    write(sprintf("You %s %s.\n", POSITION_D->query_you_move_action(pos), direction));
    say(sprintf("%s %s %s.\n", who->query_name(), POSITION_D->query_other_move_action(pos), direction));
    who->event_move(exits[direction]["destination"]);
    // Someone has arrived from somewhere
    say(sprintf("%s %s from %s.\n", who->query_name(), POSITION_D->query_other_move_action(pos), inverse));
    who->call_verb("look", "");
    return 1;
}

varargs int event_go(string direction, object who) {
    int pos;
    mapping exits = query_exits();
    string inverse = invert_cardinal_direction(direction);
    if (!who) {
        who = this_player();
    }
    pos = who->query_position();
    write(sprintf("You %s %s.\n", POSITION_D->query_you_move_action(pos), direction));
    say(sprintf("%s %s %s.\n", who->query_name(), POSITION_D->query_other_move_action(pos), direction));
    who->event_move(exits[direction]);
    say(sprintf("%s %s from %s.\n", who->query_name(), POSITION_D->query_other_move_action(pos), inverse));
    who->call_verb("look", "");
    return 1;
}