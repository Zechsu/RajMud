#ifndef __DAEMONS_H__
#define __DAEMONS_H__

#define SECURE_D                "daemon/secure_d"
#define TERM_D                  "daemon/terminal_d"
#define RACE_D                  "daemon/race_d"
#define MATERIAL_D              "daemon/material_d"
#define SKILL_D                 "daemon/skill_d"
#define NATURE_D                "daemon/nature_d"
#define POSITION_D              "daemon/position_d"
#define LOG_D                   "daemon/log_d"
#define GENDER_D                "daemon/gender_d"
#define VNUM_D                  "daemon/vnum_d"

// FUNCTIONS
#define Material(x)             MATERIAL_D->query_material(x)
#define Race(x)                 RACE_D->query_race_file(x)
#define Skill(x)                SKILL_D->query_skill(x)
#define Log(x, y)               LOG_D->log(x, y);

#endif
