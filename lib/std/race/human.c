#include <globals.h>

inherit LIB_RACE;

void create() {
    ::create();
}

string query_race_name() {
    return "human";
}

mapping query_race_body() {
    return ([
             "head":([
                      "critical":1,
                      "children":0,
                      ]),
             "upper body":([
                            "critical":0,
                            "children":([
                                         "right arm":([
                                                       "critical":0,
                                                       "children":0
                                                       ]),
                                         "left arm":([
                                                      "critical":0,
                                                      "children":0
                                                      ])
                                         ])
                            ]),
             "lower body":([
                            "critical":0,
                            "children":([
                                         "right leg":([
                                                       "critical":0,
                                                       "children":0
                                                       ]),
                                         "left leg":([
                                                      "critical":0,
                                                      "children":0
                                                      ])
                                         ])
                            ])
             ]);
}
