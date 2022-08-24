private string cwd;

void create() {
    if (cwd == 0 || !cwd || cwd == "") {
        cwd = "/";
    }
}

string query_cwd()
{
    return cwd;
}

int set_cwd(string str) {
    cwd = str;
    return 1;
}

int query_shell() {
    return 1;
}