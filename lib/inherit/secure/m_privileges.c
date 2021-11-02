#include <globals.h>

nosave string* search_paths;

void create() {
    debug_message("Setting privs for " + TO->query_name());
    search_paths = SECURE_D->query_search_paths(TO->query_name());
}

string refresh_search_paths() {
    search_paths = SECURE_D->query_search_paths(this_object()->query_name());
    return "Refreshed paths\nCurrent paths: " + dump_variable(search_paths);
}

string* query_search_paths() {
    return search_paths;
}
