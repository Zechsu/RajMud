#include <lib.h>
#include <modules.h>

inherit BASE;
inherit LIB_RACE;
inherit LIB_POSITION;
inherit LIB_COMMAND;
inherit LIB_COMBAT;
inherit M_DESC;
inherit M_SKILLS;
inherit M_TRAITS;
inherit M_TITLE;
inherit M_INVENTORY;
inherit M_VISIBLE;
inherit M_ATTRIBUTES;
inherit M_ATTACKS;

private string name;
private string current_room;
private nosave int busy = 0;

void create() {
    race::create();
    position::create();
    combat::create();
    m_visible::create();
    m_attributes::create();

    enable_commands();
    if (!current_room) {
        current_room = TEST_ROOM;
    }
}

void setup() {
    command::setup();
    setup_race_attacks();
    restore_worn_equipment();
}

void set_name(string n) {
    name = n;
    set_ids(({n, lower_case(n)}));
    set_living_name(name);
}

mixed query(string q) {
    return call_other(this_object(), "query_" + q);
}

object query_room() {
    return environment(this_object());
}

string query_name() {
    return name;
}

string query_short() {
    string title = query_title();
    if (title) {
        return sprintf("%s, %s", name, title);
    }
    else {
        return name;
    }
}

// Living descriptor
string query_long() {
    // <PRONOUN> is a <RACE>
    string ret = sprintf("%s is a %s. ", capitalize(query_pronoun()), query_race());
    object* worn = query_worn();

    string tmp = this_object()->severed_attributes();
    ret += tmp? tmp + "%^RED%^.%^RESET%^" : "";

    if (sizeof(worn) != 0) {
        ret += sprintf("\n%s is equipped with: ", capitalize(query_pronoun()));
        foreach (object w in worn) {
            ret += sprintf("\n  %-30s %-30s", w->query_short(), w->worn_attributes());
        }
    }
    return ret;
}

int is_living() {
    return 1;
}

varargs int event_move(mixed dest, int flag) {
    if (!busy) {
        ::move(dest);
        if (!flag) {
            current_room = dest;
        }
        return 1;
    }
    return 0;
}

string query_current_room() {
    return current_room;
}

int force_me(string cmd) {
    return command(cmd);
}

varargs void set_busy(int arg) {
    if (!arg) {
        busy = 1;
    }
    else {
        busy = 0;
    }
}

void receive_message(string newclass, string msg)
{
    if (this_object()->query_no_color() == 0) {
        msg = TERM_D->parse_pinkfish(msg);
    }
    else {
        msg = TERM_D->parse_pinkfish(msg, 1);
    }
    receive(msg);
}
