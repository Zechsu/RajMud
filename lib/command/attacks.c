#include <command.h>

int main(string arg) {
    string* keys;
    mapping attacks = this_player()->query_attacks();
    string attack;
    if (!attacks || !sizeof(attacks)) {
        return notify_fail("You do not have any means of attacking.\n");
    }

    if (!arg || trim(arg) == "") {
        attacks = filter_array(attacks, (: this_player()->is_attack_enabled($1) :));
        keys = keys(attacks);
        write("/---------------------------\\\n");
        write(sprintf("| %13-s %s    |\n", "Attack", "Priority"));
        write(">---------------------------<\n");
        foreach (attack in keys) {
            write(sprintf("| %15-s (%-2d)      |\n", attack, attacks[attack]["priority"]));
        }
        write("\\---------------------------/\n");
        return 1;
    }
    if (arg == "disabled") {
        attacks = filter_array(attacks, (: !this_player()->is_attack_enabled($1) :));
        keys = keys(attacks);
        if (sizeof(keys)) {
            write("/---------------------------\\\n");
            write(sprintf("| %13-s %s    |\n", "Attack", "Priority"));
            write("|---------------------------|\n");
            foreach (attack in keys) {
                write(sprintf("| %15-s (%-2d)      |\n", attack, attacks[attack]["priority"]));
            }
            write("\\---------------------------/\n");
            return 1;
        }
        else {
            return notify_fail("You have not disabed any attacks.\n");
        }
    }
    else if (sscanf(arg, "stop %s", attack) == 1) {
        if (this_player()->disable_attack(attack)) {
            tell_object(this_player(), "You stop attacking with " + attack + ".\n");
            return 1;
        }
        else
            return notify_fail("You do not have such attack.\n");
    }
    else if (sscanf(arg, "start %s", attack) == 1) {
        if (this_player()->enable_attack(attack)) {
            tell_object(this_player(), "You start attacking with " + attack + ".\n");
            return 1;
        }
        else
            return notify_fail("You do not have such attack.\n");
    }
    return notify_fail("Something went wrong!\n");
}