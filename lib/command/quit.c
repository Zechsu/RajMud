#include <command.h>

#ifdef __NO_ENVIRONMENT__
#define say(x) shout(x)
#endif

int
main(string arg)
{
    this_player()->save();
    write("Bye.\n");
    say((string)previous_object()->query_name()
        + " leaves this reality.\n");
    previous_object()->remove();
    return 1;
}
