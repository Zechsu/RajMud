#ifndef __DAEMONS_H__
#define __DAEMONS_H__

#define SECURE_D                "daemon/secure_d"
#define TERM_D                  "daemon/terminal_d"
#define RACE_D                  "daemon/race_d"
#define MATERIAL_D              "daemon/material_d"
// FUNCTIONS
#define Material(x)             MATERIAL_D->query_material(x)
#define Race(x)                 RACE_D->query_race_file(x)

#endif
