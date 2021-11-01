#include <globals.h>

string* search_paths;

void create() {
    search_paths = SECURE_D->query_search_paths(this_player()->query_name());
}

string refresh_paths() {
    search_paths = SECURE_D->query_search_paths(this_player()->query_name());
    return "Refreshed paths\nCurrent paths: " + dump_variable(search_paths);
}

string* query_search_paths() {
    return search_paths;
}
