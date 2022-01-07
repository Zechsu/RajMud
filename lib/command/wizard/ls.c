#include <command.h>

int main(string str) {
    object tp = this_player();
    mixed dir = get_dir(tp->query_cwd());
    int size = sizeof(dir);
    write(tp->query_cwd() + "\n");
    for (int i = 0; i < size; i++) {
        if (get_dir(tp->query_cwd() + dir[i] + "/")) {
            write("%^GREEN%^" + sprintf("%-30.30s", dir[i] + "/") + "%^RESET%^");
        }
        else {
            write(sprintf("%-30.30s", dir[i]));
        }
        if (i % 4 == 0) {
            write("\n");
        }
    }
    write("\n");
    return 1;
}
