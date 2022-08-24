#include <command.h>

int main(string str) {
    object tp = this_player();
    string cwd = tp->query_cwd();

    if (!str) {
        str = "realm/" + tp->query_account_link()->query_account_name();
    }
    else if (str[0] != '/' && str[0] != '~' && str[0] != '^') {
        str = tp->query_cwd() + "/" + str;
    }
    str = sanitize_path(str);

    if (file_size(str) == -2) {
        tp->set_cwd(str);
        return 1;
    } else {
        return notify_fail("Invalid directory.\n");
    }
}
