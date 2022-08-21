#include <command.h>

#define ANSI(p) sprintf("%c["+(p)+"m", 27)

int main(string arg) {
    mapping data = ([
        "RED":ANSI(31), "GREEN":ANSI(32),
        "YELLOW": ANSI(33), "BLUE": ANSI(34), "CYAN":ANSI(36),
        "MAGENTA":ANSI(35), "WHITE": ANSI(37)
    ]);

    string* keys = keys(data);
    string* values = values(data);
    int sz = sizeof(keys);

    for (int i = 0; i < sz; i++) {
        if (i % 3 == 0 && i != 0)
            write("\n");
        write(sprintf("    %s%15-s%s", values[i], keys[i], ANSI(0)));
        write(ANSI(0));
    }
    write("\n");
    return 1;
}