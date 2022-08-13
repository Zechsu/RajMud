#include </descriptors/attack.h>;

string* describe(mapping attack_descriptor) {
    string tmp = replace_string("$N $vstab $T in the $L", "$L", attack_descriptor[LOCATION]);
    return compose_message(attack_descriptor[ATTACKER], tmp, attack_descriptor[DEFENDER]);
}