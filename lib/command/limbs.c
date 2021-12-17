#include <command.h>

int main(string str) {
    object tp = TP;
    write("You have: \n");
    foreach(string limb in tp->query_limbs()) {
        write(limb + "\n");
    }
    return 1;
}
