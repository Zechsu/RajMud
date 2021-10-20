#include <globals.h>

private nomask int valid_name(string name);

// needs fixed to handle passwords

#ifdef __INTERACTIVE_CATCH_TELL__
void catch_tell(string str) {
    receive(str);
}
#endif

void receive_message(string newclass, string msg) {
    msg = TERM_D->parse_pinkfish(msg, 1);
    receive(msg);
}

void
logon()
{ 
#ifdef __NO_ADD_ACTION__
    set_this_player(this_object());
#endif
#ifdef __PACKAGE_UIDS__
    seteuid(getuid(this_object()));
#endif
    write("Welcome to RajMud!\n\n");
    //cat("/etc/motd");
    write("\nName thyself ");
    input_to("accept_name", 2); // 2 means no command escaping with !
}

private void create_user_object(string name) {
    object user;

    user = new("clone/user");
    user->set_name(name);
    exec(user, this_object());
    SECURE_D->make_user(name);
    user->setup();
    user->move(user->query_current_room());
    user->set_ids(({name}));
    destruct(this_object());
}

private void ensure_password_folder() {
    if (sizeof( "u/passwords") == 0) {
        mkdir("u/passwords");
    }
}

private string password_file(string name) {
    return "u/passwords/" + name;
}

private int user_exists( string name ) {
    return sizeof( stat( password_file(name) ) ) > 0;
} 

void accept_name(string name) {
    if ( trim(name) == "" ) {
        destruct(this_object());
        return;
    }
    if (valid_name(name)) {
        if ( user_exists(name) ) {
            write("Welcome back, " +name+ "\nEnter password: ");
            input_to("accept_password", 3, name); // 3 is same as 2 + characters won't be shown
        } else if ( valid_name(name) ) {
            write("Welcome to RajMud, " +name+ "\nEnter password: ");
            input_to("create_password", 3, name);
        }
    } 
    else {
        write("\nName thyself");
        input_to("accept_name", 2);
        return;
    }

}

private nomask int valid_name(string str) {
    int len = strlen(str);

    if ( len > 18 ) {
        write("Sorry, your name is too long!");
        return 0;
    }

    if (!regexp(str, "^[a-zA-Z ,.'-]+$")) {
        write("\nInvalid name!");
        return 0;
    }

    return 1;
}

private nomask int matches_password(string password, string str) {
    if (password[0..2] == "$6$") {
        return crypt(str, password) == password;
    }
    else {
        if (oldcrypt(str, password) == password) {
            write("Upgrading password to SHA512");
            password = crypt(str, 0);
            return 1;
        }
    }
    return 0;
} 

void accept_password(string password, string name) {
    string str = read_file( password_file( name) );
    object already;
    if ( matches_password(str, password)) {
        write("\n\nWelcome back!\n");
        already = find_player(name);
        if (already) {
            remove_interactive(already);
        }
        create_user_object(name);
        return;
    }
    write("\nIncorrect password! Try again");
    write("\nName thyself");
    input_to("accept_name");
}

void create_password(string password, string name) {
    if (strlen(password) < 6 && !regexp(password, "^[a-zA-Z0-9]+$")) {
        write("Invalid password! Try again");
        write("\nEnter password: ");
        input_to("create_password", 3, name);
        return;
    }
    write("\nRepeat your password: ");
    input_to("repeat_password", 3, password, name);
}

void repeat_password(string vpass, string opass, string name) {
    if (vpass != opass) {
        write("\nPasswords do not match! Try again!");
        write("\nName thyself");
        input_to("accept_name", 2);
        return;
    }

    ensure_password_folder();
    write_file( password_file(name), crypt(opass, 0), 1 );
    create_user_object(name);
}