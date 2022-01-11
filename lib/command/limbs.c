#include <command.h>

int main(string str) {
    object tp = this_player();
    mapping body = tp->query_body();
    string* limbs = sort_array(tp->query_limbs(), (: strcmp($1, $2) :));
    write("Anatomy report: \n");
    foreach(string limb in limbs) {
        write(sprintf("%-15s %-15s\n", limb, body[limb]["severed"]? "severed":"okay"));
    }
    return 1;
}
