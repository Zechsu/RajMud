#include <lib.h>
#include <daemons.h>

inherit CLEAN_UP;

object link;

private nomask int valid_name(string name);
void character_list();
void write_account_options();
void goto_account_menu();

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

void logon()
{ 
#ifdef __NO_ADD_ACTION__
    set_this_player(this_object());
#endif
#ifdef __PACKAGE_UIDS__
    seteuid(getuid(this_object()));
#endif
    write("Welcome to RajMud!\n\nName thyself (Case insensitive)\n");
    //cat("/etc/motd");
    input_to("accept_name", 2); // 2 means no command escaping with !
}

private void create_user_object(string name) {
    object user;
    SECURE_D->make_user(name);

    user = new(PLAYER_OB);
    user->set_name(name);
    exec(user, this_object());
    user->setup();
    user->move(user->query_current_room());
    // until chargen
    user->set_race("human");
    user->set_gender(1);
    user->set_trait("handedness", "right");
    user->set_skill_level("constitution", 2);
    Log("login", strftime("%D [%H:%M:%S] ", time()) + name);
    // Send the discord hello gmcp message to set-up the rich pressence
    user->gmcp("External.Discord.Hello");

    destruct(this_object());
}

private void ensure_password_folder() {
    if (sizeof( "u/passwords") == 0) {
        mkdir("u/passwords");
    }
}

private string account_file(string name) {
    return "/data/accounts/" + lower_case(name) + ".o";
}

private int character_exists(string name) {
    return sizeof(stat(player_save_file(name))) > 0;
}

private int account_exists(string name) {
    return sizeof(stat(account_file(name))) > 0;
}

void setup_link(string name) {
    link = new("/inherit/secure/link", lower_case(name));
    link->restore_me();
}

void accept_name(string name) {
    if ( trim(name) == "" || trim(name) == "quit") {
        destruct(this_object());
        return;
    }
    // Remove spaces at the end and beggining of names so we don't fuck sprintfs
    name = rtrim(name);
    name = ltrim(name);
    if (valid_name(name)) {
        if ( account_exists(name) ) {
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
        write("\nSorry, your name is too long!\n");
        return 0;
    }

    if (!regexp(str, "^[a-zA-Z ,.'-]+$")) {
        write("\nInvalid name!\n");
        return 0;
    }

    return 1;
}

// password - actual password (encrypted)
// str - what the player wrote (text)
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
    link = new("/inherit/secure/link", lower_case(name));
    // since we're here, we know for a fact that the saved object does indeed exist
    link->restore_me();
    if ( link->check_password(password)) {
        write("\n\nWelcome back!\n");
        goto_account_menu();
        return;
    }
    link = 0;
    write("\nIncorrect password! Try again\n");
    write("\nName thyself");
    input_to("accept_name");
}

void create_password(string password, string name) {
    if (strlen(password) < 6 && !regexp(password, "^[a-zA-Z0-9]+$")) {
        write("Invalid password! Try again\n");
        write("\nEnter password: ");
        input_to("create_password", 3, name);
        return;
    }
    write("\nRepeat your password:\n");
    input_to("repeat_password", 3, password, name);
}

void write_account_options() {
    write("Choose an option:\n");
    write("p: Choose a character\n");
    write("n: Make a new character\n");
    write("q: Quit\n");
}

void repeat_password(string vpass, string opass, string name) {
    if (vpass != opass) {
        write("\nPasswords do not match! Try again!\n");
        write("\nName thyself\n");
        input_to("accept_name", 2);
        return;
    }

    // ensure_password_folder();
    // write_file( password_file(name), crypt(opass, 0), 1 );
    // create_user_object(name);
    link = new("/inherit/secure/link", lower_case(name));
    link->set_password(crypt(opass, 0));
    link->save_me();
    goto_account_menu();
}

void goto_account_menu() {
    write_account_options();
    input_to("account_menu");
}

void create_new_character(string name) {
    if (valid_name(name)) {
        if (character_exists(name)) {
            write("Another character with that name already exists!\n");
            write_account_options();
            input_to("account_menu");
            return;
        }
        link->add_character(name, "human");
        link->save_me();
        create_user_object(name);
    }
    else {
        goto_account_menu();
    }
}

void account_menu(string option) {
    switch (trim(lower_case(option))) {
        case "p":
            character_list();
            break;
        case "n":
            write("Enter a character name:\n");
            input_to("create_new_character");
            break;
        case "q":
            destruct(this_object());
            return;
        default:
            goto_account_menu();
    }
}

void character_list() {
    string* chars = link->query_characters();
    if (chars) {
        for (int i = 1; i < sizeof(chars)+1; i++) {
            write(i + ". " + chars[i-1] + "\n");
        }
        input_to("character_select");
    }
    else {
        write("\nYou do not have any characters!\n\n");
        write_account_options();
        input_to("account_menu");
    }
}

void character_select(string input) {
    string* chars = link->query_characters();
    int len = sizeof(chars);
    int num = to_int(input);

    if (num < 1 || num > len) {
        write("Invalid character!\n");
        write_account_options();
        input_to("account_menu");
    }
    else {
        object user;
        user = new(PLAYER_OB);
        user->set_name(chars[num-1]);
        exec(user, this_object());
        user->setup();
        user->move(user->query_current_room());
        write("Welcome, " + user->query_name() + "\n");
        user->force_me("look");
    }
}