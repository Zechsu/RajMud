#include <lib.h>
#include <modules.h>
#include <daemons.h>

inherit M_ALIASES;
inherit M_PRIVILEGES;

void setup() {
    m_privileges::setup();
    add_action("commandHook", "", 1);
}

string process_input(string arg) {
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

int commandHook(string arg) {
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