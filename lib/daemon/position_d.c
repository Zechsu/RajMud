#include <positions.h>

/**
 * Returns string of position id.
 * 
 * @param {int} position - The id of the position.
 * @return Returns string of position name or 0 if invalid id.
 */
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
