#include <command.h>

int main(string str) {
    object tp = TP;
    mapping limbs = tp->query_limbs();
    write("You have: \n");
    foreach(string limb in keys(limbs)) {
        write(limb + "\n");
        if (mapp(limbs[limb]["children"])) {
            foreach(string child in keys(limbs[limb]["children"])) {
               write(" - " + child + "\n");
            }
        }
    }
    return 1;
}
