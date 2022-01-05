#include <globals.h>

int main(string str) {
    object tp = this_player();
    string* skills = tp->query_skills();
    if (sizeof(skills)) {
        write("Your skills are:\n");
        foreach (string skill in skills) {
            int level = tp->query_skill_level(skill);
            float required_exp = to_float(Skill(skill)->required_exp(level));
            int exp = tp->query_skill_exp(skill);
            string percent = sprintf("%.2f", exp/required_exp);
            write(capitalize(skill) + " : " + level + " (" + percent + "%)" + "\n");
            return 1;
        }
    }
    else {
        return notify_fail("You're not skilled in anything.\n");
    }
}
