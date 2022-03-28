#include <positions.h>

mixed query_move_action(int position) {
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
