#include <command.h>
#include <globals.h>

string help() {
    return "Syntax:\n" +
            "modify short <description>\n" +
            "modify long <description>\n";
}

int main(string str) {
    object env;
    string* code;
    string what, change, bname;
    if (!str) {
        return notify_fail(help());
    }
    if (sscanf(str, "%s %s", what, change) == 2) {
        env = environment(this_player());
        bname = base_name(env);
        switch (what) {
        case "short":
            code = explode(read_file(bname + ".c"), "\n");
            for (int i = 0; i < sizeof(code); i++) {
                if (strsrch(code[i], "set_short") != -1) {
                    code[i] = "    set_short(\"" + change + "\");";
                }
            }
            write_file(base_name(env) + ".c", implode(code, "\n"), 1);
            env->set_short(change);
            return 1;
        case "long":
            code = explode(read_file(bname + ".c"), "\n");
            for (int i = 0; i < sizeof(code); i++) {
                if (strsrch(code[i], "set_long") != -1) {
                    code[i] = "    set_long(\"" + change + "\";";
                }
            }
            write_file(bname + ".c", implode(code, "\n"), 1);
            env->set_long(change);
            return 1;
        }
    }
}
