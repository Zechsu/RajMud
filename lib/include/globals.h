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
#define DOMAINS_DIR "/domains"

#define VIRTUAL_D  "/single/virtual"

#define LOGIN_OB   "/clone/login"
#define USER_OB    "/clone/user"
#define VOID_OB    "/single/void"
#define TEST_ROOM  "/domains/test/rooms/testr"

#define ROOT_UID     "Root"
#define BACKBONE_UID "Backbone"

#define BASE            "/inherit/base"
#define OVERRIDES_FILE  "/single/simul_efun"

#define COMMAND_PREFIX "/command/"

// modules
#define M_PRIVILEGES  "/inherit/secure/m_privileges"
#define M_ALIASES     "/inherit/secure/m_aliases"
#define M_DESC        "/inherit/modules/m_description"
#define M_EXITS       "/inherit/modules/m_exits"

// Components
#define LIB_ROOM      "/inherit/room"
#define LIB_ITEM      "/inherit/item"
#define LIB_PROP      "/inherit/prop"
#define LIB_DOOR      "/inherit/door"
#define LIB_BODY      "/inherit/body"
#define LIB_RACE      "/inherit/race"

// classes for message() efun.
#define M_STATUS "status"
#define M_SAY    "say"

#define CLEAN_UP "/inherit/clean_up"
