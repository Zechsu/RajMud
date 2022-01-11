#include <command.h>
#include <positions.h>

int main(string arg) {
    if (this_player()->query_position() == CRAWLING)
        return notify_fail("You're already crawling.\n");
    return this_player()->event_crawl();
}