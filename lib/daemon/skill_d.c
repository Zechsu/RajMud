#include <globals.h>

private mapping skills = ([]);

void create() {
    foreach (string file in get_dir(SKILLS_DIR + "/*.c")) {
        string tmp = SKILLS_DIR + "/" + file;
        string name;

        if (!load_object(tmp)) {
            debug_message("Couldn't load skill " + tmp + "\n");
            continue;
        }
        name = tmp->query_name();
        skills[name] = tmp;
    }
}

object query_skill(string skill) {
    return skills[skill];
}

void give_exp(mixed who, string skill, int exp) {
    if (stringp(who)) {
        who = find_living(who);
    }
    if (!who) return;
    who->give_exp(skill, exp);
}