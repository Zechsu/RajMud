private string account_name;
private mapping bodies;
private string password;

void create(string name) {
    account_name = name;
    bodies = ([]);
}

void set_password(string newpass) {
    password = newpass;
}

void save_me() {
    save_object("/data/accounts/" + account_name + ".o");
}

void restore_me() {
    restore_object("/data/accounts/" + account_name + ".o");
}

int check_password(string pass) {
    return crypt(pass, password) == password;
}

string query_password() {
    return password;
}

void add_character(string name, string race) {
    if (!bodies) {
        bodies = ([]);
    }
    if (!bodies[name]) {
        bodies[name] = race;
    }
}

string* query_characters() {
    if (!sizeof(bodies) || !bodies) {
        return 0;
    }
    return keys(bodies);
}

int query_characters_count() {
    return sizeof(bodies);
}

string query_account_name() {
    return account_name;
}