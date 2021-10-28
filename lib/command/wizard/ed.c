#include <globals.h>

int
main(string file)
{
    if (!file) {
        return notify_fail("No filename\n");
    }
    if (file[0] == '/') {
        file = TP()->query_cwd() + ".c";
    }
    else {
        file = TP()->query_cwd() + file + ".c";
    }
    // need to call resolve_path() and query_cwd()
#ifdef __OLD_ED__
    ed(file);
#else
    this_player()->start_ed(file);
#endif
    return 1;
}
