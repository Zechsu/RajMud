inherit STD_RACE;

void create() {
    set_race_name("human");
    set_race_body(([
        "head":([
            "critical":1,
            "parent":0,
            "severed":0,
        ]),
        "torso":([
            "critical":1,
            "parent":0,
            "severed":0,
        ]),
        "right arm":([
            "critical":0,
            "parent":"torso",
            "severed":0,
        ]),
        "left arm":([
            "critical":0,
            "parent":"torso",
            "severed":0,
        ]),
        "right leg":([
            "critical":0,
            "parent":"torso",
            "severed":0,
        ]),
        "left leg":([
            "critical":0,
            "parent":"torso",
            "severed":0,
        ]),
        "right hand":([
            "critical":0,
            "parent":"right arm",
            "severed":0,
        ]),
        "left hand":([
            "critical":0,
            "parent":"left arm",
            "severed":0,
        ]),
    ]));
}

string* query_legs() {
    return ({"right leg", "left leg"});
}