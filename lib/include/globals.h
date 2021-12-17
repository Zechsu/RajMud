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
#include "modules.h"

#define ENV(x)      environment(x)
#define TO        this_object()
#define TP        this_player()

#define MUD_VERSION     "0.1.3"

#define SINGLE_DIR  "/single"
#define CONFIG_DIR  "/etc"
#define LOG_DIR     "/log"
#define DAEMON_DIR  "/daemon"
#define DOMAINS_DIR "/domains"
#define PLAYERS_DIR "/data/users"
#define RACES_DIR   "/std/race"

#define VIRTUAL_D  "/single/virtual"

#define LOGIN_OB   "/clone/login"
#define PLAYER_OB  "/clone/player"
#define VOID_OB    "/single/void"
#define TEST_ROOM  "/domains/test/rooms/testr"
#define VOID_ROOM  "/domains/void/void"

#define ROOT_UID     "Root"
#define BACKBONE_UID "Backbone"

#define BASE            "/inherit/base"
#define OVERRIDES_FILE  "/single/simul_efun"

#define COMMAND_PREFIX "/command/"

// Components
#define LIB_ROOM            "/inherit/room"
#define LIB_ITEM            "/inherit/item"
#define LIB_PROP            "/inherit/prop"
#define LIB_DOOR            "/inherit/door"
#define LIB_CONTAINER       "/inherit/container"
#define LIB_PERSIST         "/inherit/persist"
#define LIB_BODY            "/inherit/body"
#define LIB_RACE            "/inherit/race"
#define LIB_AUTOSAVE        "/inherit/user/autosave"
#define LIB_LIVING          "/inherit/living"

// classes for message() efun.
#define M_STATUS "status"
#define M_SAY    "say"

// GENERICS
#define STD_RACE            "/std/race"

#define CLEAN_UP "/inherit/clean_up"

