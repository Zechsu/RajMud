#include <globals.h>

inherit LIB_ROOM;

void create() {
    ::create();
    set_short("Testing room for test purposes");
    set_long("This is a room only for testing. Please do not do anything else as that will make the testing room a non-testing room\n
    And thus leading to a paradox!!! And we don't want that!");
}