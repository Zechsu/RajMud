#include <globals.h>

int main(string file)
{
    object tp = this_player();
    file = tp->query_cwd() + file + ".c";
    if (!file || trim(file) == "") {
        return notify_fail("rm which file?\n");
    }
    // need to call resolve_path() and query_cwd()
    if (rm(file)) {
        write("Removed " + file + "\n");
        return 1;
    }
    else {
        return notify_fail("Couldn't find file " + file + "\n");
    }
}
