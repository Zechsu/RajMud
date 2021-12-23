#include <command.h>

int main(string str) {
    object tp = TP;
    string* limbs = sort_array(tp->query_limbs(), (: strcmp($1, $2) :));
    write("You have: \n");
    foreach(string limb in limbs) {
        write(limb + "\n");
    }
    return 1;
}
