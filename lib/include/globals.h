// file: globals.h

#ifdef __SENSIBLE_MODIFIERS__
#define staticf protected
#define staticv nosave
#else
#define staticf static
#define staticv static
#endif

#include "tests.h"
#include "daemons.h"

#define SINGLE_DIR "/single"
#define CONFIG_DIR "/etc"
#define LOG_DIR    "/log"
#define DAEMON_DIR "/daemon"

#define VIRTUAL_D  "/single/virtual"

#define LOGIN_OB   "/clone/login"
#define USER_OB    "/clone/user"
#define VOID_OB    "/single/void"

#define ROOT_UID     "Root"
#define BACKBONE_UID "Backbone"

#define BASE            "/inherit/base"
#define OVERRIDES_FILE  "/single/simul_efun"

#define COMMAND_PREFIX "/command/"

// modules
#define M_PRIVILEGES "/inherit/secure/m_privileges"

// classes for message() efun.
#define M_STATUS "status"
#define M_SAY    "say"

#define CLEAN_UP "/inherit/clean_up"
