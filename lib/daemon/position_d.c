#include <positions.h>

mixed query_you_move_action(int position) {
    switch (position) {
        case STANDING:
            return "walk";
        case FLYING:
            return "fly";
        case SITTING:
            return 0;
        case CRAWLING:
            return "crawl";
        default:
            return 0;
    }
}

mixed query_other_move_action(int position) {
    switch (position) {
        case STANDING:
            return "walks";
        case FLYING:
            return "flies";
        case SITTING:
            return 0;
        case CRAWLING:
            return "crawls";
        default:
            return 0;
    }
}