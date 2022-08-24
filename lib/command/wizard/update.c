#include <globals.h>

#define U_RECURSIVE     1 << 0

int main(string file)
{
    object obj;
    object tp = this_player();
    object* users;
    string path;
    string tmp;
    string* cmd;
    int flags = 0;

    // need to call resolve_path() and query_cwd()
    if (!file) {
        return notify_fail("Update what?\n");
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
        return 1;
    }

    if (file[0] != '/' && file[0] != '~' && file[0] != '^') {
        path = tp->query_cwd();
        path = sanitize_path(path + "/" + file);
    }
    else {
        path = sanitize_path(file);
    }

    if (obj = find_object(path)) {
        if (flags & U_RECURSIVE) {
            string* ancestors = deep_inherit_list(obj);
            int i = sizeof(ancestors);
            while (i--) {
                object anc = find_object(ancestors[i]);
                destruct(anc);
                load_object(ancestors[i]);
                write("Updated ancestor " + ancestors[i] + "\n");
            }
            return 1;
        }
        destruct(obj);
        load_object(file);
        write("Updated " + file + "\n");
        return 1;
    }
    else {
        if (load_object(file)) {
            load_object(file);
            write("Updated " + file + "\n");
            return 1;
        }
        else if (obj = present(file, environment(this_player()))) {
            string basename = base_name(obj);
            destruct(obj);
            if (obj = load_object(basename)) {
                obj->move(environment(this_player()));
                write("Updated " + file + "\n");
                return 1;
            }
            return notify_fail("Could not update " + file + "\n");
        }
    }
    return 1;
}
