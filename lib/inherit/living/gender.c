#include <daemons.h>

private int gender;

void set_gender(int g) {
    gender = g;
}

int query_gender() {
    return gender;
}

string query_possessive_determiner() {
    return GENDER_D->query_possessive_determiner(gender);
}

string query_pronoun() {
    return GENDER_D->query_pronoun(gender);
}

string query_determiner() {
    return GENDER_D->query_determiner(gender);
}

string query_reflexive() {
    return GENDER_D->query_reflexive(gender);
}