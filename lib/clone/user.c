// mudlib:   Lil 
// file:     user.c
// purpose:  is the representation of an interactive (user) in the MUD

#include <globals.h>

inherit BASE;
inherit M_PRIVILEGES;
inherit M_ALIASES;
inherit LIB_BODY;
inherit LIB_AUTOSAVE;

private string name;
private string current_room;
string cwd;
private int no_color = 1;
private nosave int start_play = time();
private nosave int end_play = 0;
private int play_time = 0;
//forward declarations

string query_save_folder();
void save();

//end forward declarations

#ifdef __INTERACTIVE_CATCH_TELL__
void catch_tell(string str) {
    receive(str);
}
#endif

// replace this with a functioning version.

string query_cwd()
{
    return cwd;
}

int set_cwd(string str) {
    cwd = str;
    return 1;
}

void set_color(int to) {
    if (to == 1) {
        no_color = 0;
    }
    else {
        no_color = 1;
    }
}

// logon: move this to /single/login.c when login.c gets written.

void
logon()
{
    write("Welcome to RajMud.\n> ");
}

// query_name: called by various objects needing to know this user's name.

string
query_name()
{
    return name;
}

void
set_name(string arg)
{
//  may wish to add security to prevent just anyone from changing
//  someone else's name.
    name = arg;
}

// called by the present() efun (and some others) to determine whether
// an object is referred as an 'arg'.

int
id(string arg)
{
    return (arg == query_name()) || base::id(arg);
}

#ifndef __OLD_ED__
void
write_prompt() {
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

void
start_ed(string file) {
    write(ed_start(file, 0));
}
#endif

#ifdef __NO_ADD_ACTION__
void
exec_command(string arg) {
    string *parts = explode(arg, " ");
    string verb = sizeof(parts) ? parts[0] : "";
    string rest = implode(parts[1..], " ");
    string cmd_path = COMMAND_PREFIX + verb;
    object cobj = load_object(cmd_path);

    if (cobj) {
    cobj->main(rest);
    } else {
    // maybe call an emote/soul daemon here
    }
}

void process_input(string arg) {
    exec_command(arg);
}

#else
string process_input(string arg)
{
    // possible to modify player input here before driver parses it.
    string* tmp;
    // string* ignored = ({"alias", "go", "say", "open", "close", "tp", "look"});

    // protects from sending empty commands
    if (trim(arg) == "") {
        return "";
    }

    arg = replace_string(arg, "%^", "");
    arg = replace_string(arg, "%#", "");

    // since all aliases here are lower case, typing in 'L' or 'N' should also work
    arg[0] = lower_case(arg)[0];

    if (dir_aliases[arg]) {
        return dir_aliases[arg];
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
    return implode(tmp[0..], " ");
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

void
init()
{
    // using "" as the second argument to add_action() causes the driver
    // to call commandHook() for those user inputs not matched by other
    // add_action defined commands (thus 'commandHook' becomes the default
    // action for those verbs without an explicitly associated action).
    if (this_object() == this_player()) {
        add_action("commandHook", "", 1);
    }
}
#endif

// create: called by the driver after an object is compiled.

void
create()
{
#ifdef __PACKAGE_UIDS__
    seteuid(0); // so that login.c can export uid to us
#endif
   
}

// receive_message: called by the message() efun.

void
receive_message(string newclass, string msg)
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
    set_heart_beat(1);
#ifdef __PACKAGE_UIDS__
    seteuid(getuid(this_object()));
#endif
#ifndef __NO_WIZARDS__
    enable_wizard();
#endif
#ifndef __NO_ADD_ACTION__
    set_living_name(query_name());
    enable_commands();
    add_action("commandHook", "", 1);
#else
    set_this_player(this_object());
#endif
    m_privileges::create();
    autosave::restore_player();
    autosave::restore_inventory();
    if (!current_room) {
        current_room = TEST_ROOM;
    }
    if (cwd == 0 || !cwd || cwd == "") {
        cwd = "/";
    }
}

// net_dead: called by the gamedriver when an interactive player loses
// hir network connection to the mud.

#ifndef __NO_ENVIRONMENT__
void tell_room(object ob, string msg) {
    foreach (ob in all_inventory(ob) - ({ this_object() }))
        tell_object(ob, msg);
}
#endif

void
net_dead()
{
    set_heart_beat(0);
#ifndef __NO_ENVIRONMENT__
    tell_room(environment(), query_name() + " is link-dead.\n");
#endif
}

// reconnect: called by the login.c object when a netdead player reconnects.

void
reconnect()
{
    set_heart_beat(1);
#ifndef __NO_ENVIRONMENT__
    tell_room(environment(), "Reconnected.\n");
    tell_room(environment(), query_name() + " has reconnected.\n");
#endif
}

varargs int move(mixed dest, int flag) {
    ::move(dest);
    if (!flag) {
        current_room = dest;
    }
}

string query_current_room() {
    return current_room;
}

int set_race(string race) {

}

void refresh_play_time() {
    end_play = time();
    play_time += end_play - start_play;
    start_play = time();
}

int query_play_time() {
    refresh_play_time();
    return play_time;
}
