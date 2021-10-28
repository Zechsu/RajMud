#include <command.h>

int main(string str) {
    object tp = this_player();
    mixed dir = get_dir(tp->query_cwd());
    write(tp->query_cwd() + "\n");
    foreach (string file in dir) {
        tell_object(tp, file + "\n");
    }
    return 1;
}
