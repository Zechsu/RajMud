#include <command.h>

#ifdef __NO_ENVIRONMENT__
#define say(x) shout(x)
#endif

int
main(string arg)
{
    object tp = this_player();
    tp->refresh_play_time();
    tp->save_player();
    write("Bye.\n");
    say((string)previous_object()->query_name()
        + " leaves this reality.\n");
    previous_object()->remove();
    return 1;
}
