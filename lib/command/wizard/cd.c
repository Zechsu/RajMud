#include <command.h>

int main(string str) {
    object tp = this_player();
    string cwd = tp->query_cwd();

    if (!str) {
        tp->set_cwd("/");
        write("/");
        return 1;
    }

    if (str == "..") {
        cwd[strsrch(cwd[0..<2], "/", -1)..] = "";
        tp->set_cwd(cwd + "/");
        tp->call_verb("ls", "");
        return 1;
    }

    if (stat(cwd + str + "/")) {
        tp->set_cwd(cwd + str + "/");
        tp->call_verb("ls", "");
        return 1;
    }
    else if (stat(str) != ({})) {
        tp->set_cwd(str);
        tp->call_verb("ls", "");
        return 1;
    }
    else {
        tell_object(tp, "Directory not found.\n");
        return 1;
    }
}
