#include <command.h>

int main(string str) {
    object tp = this_player();
    mixed dir = get_dir(tp->query_cwd());
    int size = sizeof(dir);
    if (!size) {
        return notify_fail("Empty directory.\n");
    }
    for (int i = 0; i < size; i++) {
        if (i % 4 == 0 && i != 0) {
            write("\n");
        }
        if (get_dir(tp->query_cwd() + dir[i] + "/")) {
            write("%^GREEN%^" + sprintf("%-20.30s", dir[i] + "/") + "%^RESET%^");
        }
        else {
            write(sprintf("%-20.30s", dir[i]));
        }
    }
    write("\n");
    return 1;
}
