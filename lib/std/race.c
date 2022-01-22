#include <globals.h>

private string race;
private mapping body;

void set_race_name(string n) {
    race = n;
}

string query_race_name() {
    return copy(race);
}

mapping query_race_body() {
    return copy(body);
}

void set_race_body(mapping b) {
    body = b;
}

int query_fingers(string hand) {
    if (body[hand]["fingers"]) {
        return body[hand]["fingers"];
    }
    return 0;
}