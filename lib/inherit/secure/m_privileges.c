#include <globals.h>

private string* search_paths;

void create() {
    search_paths = SECURE_D->query_search_paths(this_player()->query_name());
}

string* query_search_paths() {
    return search_paths;
}