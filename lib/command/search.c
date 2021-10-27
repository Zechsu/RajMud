#include <command.h>

int main(string str) {
    object tp = this_player();
    mixed result;
    if (!str) {
        result = ENV(tp)->event_searched(tp);
        if (stringp(result)) {
            return notify_fail(result);
        }
    }
}