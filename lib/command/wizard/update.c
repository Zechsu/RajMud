#include <globals.h>

#define U_RECURSIVE     1 << 0

int main(string file)
{
    object obj;
    object tp = this_player();
    object* users;
    string tmp;
    string* cmd;
    int flags = 0;

    // need to call resolve_path() and query_cwd()
    if (!file) {
        return notify_fail("update what?\n");
    }

    cmd = explode(file, "-");
    file = rtrim(cmd[0]);

    foreach (string flag in cmd[1..]) {
        switch (trim(flag)) {
            case "r": {
                flags ^= U_RECURSIVE;
                break;
            }
        }
    }

    if (file == "here") {
        obj = ENV(tp);
        users = all_inventory(obj);
        users = filter_array(users, (: interactive($1) :));
        tmp = file_name(obj);
        foreach(object user in users) {
            user->move(VOID_ROOM);
        }
        destruct(obj);
        write("Updated " + tmp + "\n");
        foreach(object user in users) {
            user->move(tmp);
        }
    }
    if (strsrch(file, "/") != -1) {
        if (obj = find_object(file)) {
            if (flags & U_RECURSIVE) {
                string* ancestors = deep_inherit_list(obj);
                int i = sizeof(ancestors);
                while(i--) {
                    object anc = find_object(ancestors[i]);
                    destruct(anc);
                    load_object(ancestors[i]);
                    write("Updated ancestor " + ancestors[i] + "\n");
                }
            }
            destruct(obj);
            write("Updated " + file + "\n");
        }
        load_object(file);
    }
    else {
        if (obj = find_object(tp->query_cwd() + file)) {
            if (flags & U_RECURSIVE) {
                string* ancestors = deep_inherit_list(obj);
                int i = sizeof(ancestors);
                while(i--) {
                    object anc = find_object(ancestors[i]);
                    destruct(anc);
                    load_object(ancestors[i]);
                    write("Updated ancestor " + ancestors[i] + "\n");
                }
            }
            destruct(obj);
            write("Updated " + file + "\n");
        }
        load_object(tp->query_cwd() + file);
    }
    return 1;
}
