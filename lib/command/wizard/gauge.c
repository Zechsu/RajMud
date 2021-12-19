#include <command.h>

int force_me(string arg) {
    TP->call_verb(arg, "");
    return 1;
}

int main(string arg) {
    mapping before, after;
    int stime, usertime, eval_cost;

    if (!arg || arg == "") return notify_fail("Specify a command to execute.\n");
    before = rusage();
    eval_cost = TP->force_me(arg);
    after = rusage();
    usertime = after["utime"] - before["utime"];
    stime = after["stime"] - before["stime"];
    write(stime + " ms system time\n" + usertime + " ms user time\n" + eval_cost + " eval cost\n");
    return 1;
}
