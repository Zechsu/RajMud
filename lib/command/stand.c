#include <command.h>
#include <positions.h>

int main(string arg) {
    if (this_player()->query_position() == STANDING)
        return notify_fail("You're already standing.\n");
    return this_player()->event_stand();
}