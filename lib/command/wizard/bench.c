#include <command.h>

int main(string arg) {
    mapping before, after;
    int stime, usertime, eval_cost;
    int total;

    if (!arg || arg == "") return notify_fail("Specify a command to benchmark.\n");
    for (int i = 0; i < 1000; i++) {
        before = rusage();
        eval_cost += TP->force_me(arg);
        after = rusage();
        usertime += after["utime"] - before["utime"];
        stime += after["stime"] - before["stime"];
    }
    write("Ran 1000 times\n");
    write(stime/1000 + " ms systemtime\n" + usertime/1000 + " ms user time\n" + eval_cost/1000 + " eval cost\n");
    return 1;
}
