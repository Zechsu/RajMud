#include <genders.h>

string query_possessive_determiner(int gender) {
    switch (gender) {
        case MALE:
            return "his";
        case FEMALE:
            return "her";
        default:
            return "their";
    }
}

string query_pronoun(int gender) {
    switch (gender) {
        case MALE:
            return "he";
        case FEMALE:
            return "she";
        default:
            return "they";
    }
}