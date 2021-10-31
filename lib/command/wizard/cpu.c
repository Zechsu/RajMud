#include <command.h>

int main(string) {
    mapping info;
    float x, fraction;

    info = rusage();

    // time is in milisecs, convert to secs
    x = (info["utime"] + info["stime"])/1000;
    fraction = x / uptime();
    write(sprintf("CPU usage at %f\n", fraction * 100));
    return 1;
}
