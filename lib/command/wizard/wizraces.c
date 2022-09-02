#include <command.h>
#include <daemons.h>

int main(string arg) {
    string* races = RACE_D->query_races();
    foreach (string race in races) {
        tell_object(this_player(), sprintf("%10-s", race));
    }
    tell_object(this_player(), "\n");
    return 1;
}