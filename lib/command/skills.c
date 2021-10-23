#include <globals.h>

int main(string str) {
    object tp = this_player();
    mapping skills = tp->query_skills();
    if (skills) {
        write("Your skills are: \n");
        foreach (string skill, int level in skills) {
            write(skill + " : " + level + "\n");
            return 1;
        }
    }
    return notify_fail("You're not skilled in anything.\n");
}
