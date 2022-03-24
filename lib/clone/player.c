// mudlib:   Lil 
// file:     user.c
// purpose:  is the representation of an interactive (user) in the MUD

#include <globals.h>

inherit LIB_LIVING;
inherit LIB_AUTOSAVE;
inherit LIB_BIRTHDAY;
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

int query_no_color() {
    return no_color;
}

void write_prompt() {
    if (SECURE_D->query_wizard(query_name())) {
        write(query_cwd() + " > ");
        return;
    }
    write("> ");
}

// create: called by the driver after an object is compiled.

void create() {
    seteuid(0); // so that login.c can export uid to us
    ::create();
}

// receive_message: called by the message() efun.
// the meaning of 'class' is at the mudlib's discretion
void receive_message(string newclass, string msg)
{
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
    autosave::setup();
    living::setup();

    if(!query_current_room()) {
        move(TEST_ROOM);
    }
}

// net_dead: called by the gamedriver when an interactive player loses
// hir network connection to the mud.

void net_dead()
{
    set_heart_beat(0);
    debug_message(query_name() + " is link-dead.");
    save_player();
    remove();
}

// reconnect: called by the login.c object when a netdead player reconnects.

void reconnect()
{
    debug_message(query_name() + " has reconnected.");
}

void send_gmcp_data(string pkg, mixed data) {
    send_gmcp(pkg + " " + data);
}

void gmcp(string message) {
    switch (message) {
        case "External.Discord.Hello": {
            mapping info = ([]);
            mapping status = ([]);
            info += (["applicationid":"931931512385974303"]);
            status += (["largeimage":"server-icon"]);
            status += (["game":"RajMUD"]);
            status += (["starttime":time()]);
            send_gmcp_data("External.Discord.Info", json_encode(info));
            send_gmcp_data("External.Discord.Status", json_encode(status));
            break;
        }
        case "Room.Info": {
            "daemon/gmcp/info"->Info(this_player());
            break;
        }
        case "Room.Items": {
            "daemon/gmcp/info"->Items(this_player());
        }
    }
}