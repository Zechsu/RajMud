#include <command.h>

int main(string str) {
    float bytes = memory_info();
    write(sprintf("Memory usage: %.2f MB.\n", bytes/1000000));
    return 1;
}
