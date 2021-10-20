#include <command.h>

int main(string str) {
    object tp = this_player();
    int seconds = tp->query_play_time();
    int hours = (seconds / 60) / 60;
    int minutes = (seconds / 60) % 60;
    printf("You've been playing for %d hours %d minutes.\n", hours, minutes);

    return 1;
}