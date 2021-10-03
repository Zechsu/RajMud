#include <globals.h>

inherit LIB_ITEM;

void create() {
    ::create();
    set_short("sshapkata");
    set_long("I kiseloto mlqko nqkoga e bilo prqsno.");
    set_ids(({"sshapkata"}));
    set_message("on_ground", "$N is on the ground.");
}

void init() {
    add_action("do_shapka", "enter");
    add_action("exit_shapka", "exit");
}

int do_shapka(string str) {
    if (!str) {
        return 0;
    }
    
    if (lower_case(str) == "sshapkata") {
        write("%#61dbef%#THE POWER OF SSHAPKATA SUCKS YOU IN!%^RESET%^\n");
        this_player()->move("/domains/sshapkata/rooms/shapka", 1);
        return 1;
    }
    else{
        return 0;
    }
}

int exit_shapka(string str) {
    if (!str) {
        return 0;
    }
    
    if (lower_case(str) == "sshapkata") {
        write("%#61dbef%#You leave the sshapkata dimension.%^RESET%^\n");
        this_player()->move(this_player()->query_current_room());
        return 1;
    }
    else{
        return 0;
    }
}