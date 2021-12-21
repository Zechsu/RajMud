// mudlib:   Lil 
// file:     user.c
// purpose:  is the representation of an interactive (user) in the MUD

#include <globals.h>

inherit LIB_LIVING;
inherit LIB_AUTOSAVE;
inherit M_PRIVILEGES;
inherit M_ALIASES;
inherit M_SHELL;
inherit M_PLAYTIME;

private int no_color = 1;
//forward declarations

//end forward declarations

void set_color(int to) {
    if (to == 1) {
        no_color = 0;
    }
    else {
        no_color = 1;
    }
}

// query_name: called by various objects needing to know this user's name.

#ifndef __OLD_ED__
void write_prompt() {
    switch (query_ed_mode()) {
    case 0:
    case -2:
        write(":");
        break;

    case -1:
        write("> ");
        break;

    default:
        write("*\b");
        break;
    }
}

void start_ed(string file) {
    write(ed_start(file, 0));
}
#endif

string process_input(string arg)
{
    // possible to modify player input here before driver parses it.
    string* tmp;
    string* exits = ENV(TP)->query_exit_keys();
    int idx;
    // string* ignored = ({"alias", "go", "say", "open", "close", "tp", "look"});

    // protects from sending empty commands
    if (trim(arg) == "") {
        return "";
    }

    arg = replace_string(arg, "%^", "");
    arg = replace_string(arg, "%#", "");

    // since all verbs here are lower case, typing in 'L' or 'N' should also work
    arg[0] = lower_case(arg)[0];

    // expand aliases, it breaks so only 1 alias is expanded
    tmp = explode(arg, " ");
    for (int i = 0; i < sizeof(tmp); i++) {
        tmp[i] = get_alias(tmp[i]);
        break;
    }

    arg = implode(tmp[0..], " ");

     idx = member_array(arg, exits);
     if (idx != -1) {
         return "go " + exits[idx];
     }
     else {
         string* inits = map_array(exits, (: $1[0..0] :));
         idx = member_array(arg, inits);
         if (idx != -1) {
             return "go " + exits[idx];
         }
     }

    // foreach (string ign in ignored) {
    //     if (strsrch(arg, ign) != -1) {
    //         return arg;
    //     }
    // }

    tmp = explode(arg, " ");
    for (int i = 0; i < sizeof(tmp); i++) {
        tmp[i] = get_alias(tmp[i]);
        break;
    }
    return arg;
}

int commandHook(string arg)
{
    string cmd_path;
    object cobj;
    string verb = query_verb();

    foreach(string path in query_search_paths()) {
        cmd_path = path + verb;
        cobj = load_object(cmd_path);
        if (cobj) {
            return (int)cobj->main(arg);
        }
    }
    return 0;
}

int call_verb(string verb, string arg) {
    string cmd_path;
    object cobj;
    verb = lower_case(verb);

    foreach(string path in query_search_paths()) {
        cmd_path = path + verb;
        cobj = load_object(cmd_path);
        if (cobj) {
            return (int)cobj->main(arg);
        }
    }
    return 0;
}

// init: called by the driver to give the object a chance to add some
// actions (see the MudOS "applies" documentation for a better description).

void init()
{
    // using "" as the second argument to add_action() causes the driver
    // to call commandHook() for those user inputs not matched by other
    // add_action defined commands (thus 'commandHook' becomes the default
    // action for those verbs without an explicitly associated action).
    if (this_object() == this_player()) {
        add_action("commandHook", "", 1);
    }
}

// create: called by the driver after an object is compiled.

void create()
{
    seteuid(0); // so that login.c can export uid to us
    ::create();
}

// receive_message: called by the message() efun.

void receive_message(string newclass, string msg)
{
    // the meaning of 'class' is at the mudlib's discretion
    if (no_color == 0) {
        msg = TERM_D->parse_pinkfish(msg);
    }
    else {
        msg = TERM_D->parse_pinkfish(msg, 1);
    }
    receive(msg);
}

// setup: used to configure attributes that aren't known by this_object()
// at create() time such as living_name (and so can't be done in create()).

void setup()
{
    seteuid(getuid(this_object()));
    set_living_name(query_name());
    enable_commands();
    add_action("commandHook", "", 1);
    m_privileges::create();
    autosave::setup();

    if(!query_current_room()) {
        move(TEST_ROOM);
    }
}

// net_dead: called by the gamedriver when an interactive player loses
// hir network connection to the mud.

void net_dead()
{
    set_heart_beat(0);
    debug_message(query_name() + " is link-dead.\n");
    save_player();
    remove();
}

// reconnect: called by the login.c object when a netdead player reconnects.

void reconnect()
{
    debug_message(query_name() + " has reconnected.\n");
}
