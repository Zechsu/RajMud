inherit STD_RACE;

void create() {
    set_race_name("human");
    set_race_body(([
        "head":([
            "critical":1,
            "parent":0,
            "severed":0,
            "worn": ({}),
        ]),
        "torso":([
            "critical":1,
            "parent":0,
            "severed":0,
            "worn": ({}),
        ]),
        "right arm":([
            "critical":0,
            "parent":"torso",
            "severed":0,
            "worn": ({}),
        ]),
        "left arm":([
            "critical":0,
            "parent":"torso",
            "severed":0,
            "worn": ({}),
        ]),
        "right leg":([
            "critical":0,
            "parent":"torso",
            "severed":0,
            "worn": ({}),
        ]),
        "left leg":([
            "critical":0,
            "parent":"torso",
            "severed":0,
            "worn": ({}),
        ]),
        "right hand":([
            "critical":0,
            "parent":"right arm",
            "severed":0,
            "fingers":5,
            "worn": ({}),
        ]),
        "left hand":([
            "critical":0,
            "parent":"left arm",
            "severed":0,
            "fingers":5,
            "worn": ({}),
        ]),
        "genitals":([
            "critical":0,
            "parent":"torso",
            "severed":0,
            "worn": ({}),
        ]),
    ]));
}

// List of limbs that act as legs
// Used to check if living is able to stand
string* query_legs() {
    return ({"right leg", "left leg"});
}

// List of limbs that act as arms
string* query_hands() {
    return ({"right hand", "left hand"});
}

// Name of a limb that will be matched and used to determine if a entity has at least 1 usable hand
// For example used to check if has a hand to get things
string query_hand() {
    return "hand";
}
