#include <globals.h>

private nosave string* search_paths;

void setup() {
    search_paths = SECURE_D->query_search_paths(this_player()->query_name());
}

void refresh_search_paths() {
    search_paths = SECURE_D->query_search_paths(this_player()->query_name());
}

string* query_search_paths() {
    return search_paths;
}
