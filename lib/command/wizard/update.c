#include <globals.h>

int
main(string file)
{
    object obj;
    object tp = this_player();
    string tmp;

    // need to call resolve_path() and query_cwd()
    if (!file) {
        return notify_fail("update what?\n");
    }
    if (file == "here") {
        obj = ENV(tp);
        tmp = file_name(obj);
        tp->move(VOID_ROOM); 
        destruct(obj);
        write("Updated " + file + "\n");
        tp->move(tmp);
    }
    if (strsrch(file, "/") != -1) {
        if (obj = find_object(file)) {
            destruct(obj);
            write("Updated " + file + "\n");
        }
        load_object(file);
    }
    else {
        if (obj = find_object(tp->query_cwd() + file)) {
            destruct(obj);
            write("Updated " + file + "\n");
        }
        load_object(tp->query_cwd() + file);
    }
    return 1;
}
