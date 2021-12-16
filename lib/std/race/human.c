inherit STD_RACE;

void create() {
    set_race_name("human");
    set_race_body(([
        "head":([
            "critical":1,
            "parent":0,
        ]),
        "torso":([
            "critical":1,
            "parent":0,
        ]),
        "right arm":([
            "critical":0,
            "parent":"torso",
        ]),
        "left arm":([
            "critical":0,
            "parent":"torso",
        ]),
        "right leg":([
            "critical":0,
            "parent":"torso",
        ]),
        "left leg":([
            "critical":0,
            "parent":"torso",
        ]),
    ]));
}