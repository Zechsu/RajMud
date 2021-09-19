#include <command.h>
#include <globals.h>

string* add_action_commands () {
    return map( commands(), (: $1[0] :) ) - ({ "" });
}

string* commands_in_filesystem () {
    return map( get_dir( COMMAND_PREFIX + "*.c" ),
                (: $1[0..sizeof($1)-3] :) );
}

int main(string arg) {
    object cobj;
    string help;

    if (arg) {
        if (member_array(arg, commands_in_filesystem()) > -1) {
            cobj = load_object(COMMAND_PREFIX + arg + ".c");
            help = cobj->help();
            if (!help) {
                help = "No help available on that command.\n";
            }
            if (help[sizeof(help)-1..] != "\n") {
                help += "\n";
            }
            write(help);
        } else if ( member_array(arg, add_action_commands()) > -1) {
            write("No help available on that command\n");
        } else {
            write("No such command\n");
        }

        return 1;
    } else {
        write("Usage: help <command>\n");
        return 1;
    }
}

string help() {
    return "Usage: help <command>";
}