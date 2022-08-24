#include <command.h>

int main(string str) {
    object tp = this_player();
    int sz;
    string path, dir;
    string* files;

    if (!str) {
        path = tp->query_cwd();
    }
    else if (str[0] != '/' && str[0] != '~' && str[0] != '^') {
        path = tp->query_cwd();
        path = sanitize_path(path + "/" + str);
    }
    else {
        path = sanitize_path(str);
    }

    if (file_size(path) == -2) {
        if (path[<1] != '/') {
            path += "/";
        }
        dir = path;
    } else {
        dir = path[0..strsrch(path, "/", -1)];
    }

    files = get_dir(dir);
    sz = sizeof(files);
    if (sz == 0) {
        return notify_fail("Directory is empty.\n");
    }

    // if (!size) {
    //     return notify_fail("Empty directory.\n");
    // }
    for (int i = 0; i < sz; i++) {
        if (i % 4 == 0 && i != 0) {
            write("\n");
        }
        if (get_dir(tp->query_cwd() + "/" + files[i] + "/")) {
            write("%^GREEN%^" + sprintf("%-20.30s", files[i] + "/") + "%^RESET%^");
        }
        else {
            write(sprintf("%-20.30s", files[i]));
        }
    }
    write("\n");
    return 1;
}
