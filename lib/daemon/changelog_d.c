#include <daemons.h>

private int entries_count;
private mapping entries;
private int mud_version_major;
private int mud_version_minor;
private int mud_version_patch;

void create() {
    if (clonep(this_object())) {
        return;
    }
    if (!restore_object(CHANGELOG_SAVE)) {
        entries = ([]);
        entries_count = 0;
        mud_version_major = 0;
        mud_version_minor = 1;
        mud_version_patch = 0;
    }
}

mapping query_entry(int id) {
    return entries[id];
}

int query_entries_count() {
    return entries_count;
}

void add_entry(mapping entry) {
    entries_count++;
    entries += ([entries_count : entry]);

    if (entry["version"] == "major") {
        mud_version_major++;
    }
    else if (entry["version"] == "minor") {
        mud_version_minor++;
    }
    else {
        mud_version_patch++;
    }

    save_object(CHANGELOG_SAVE);
}

string query_mud_version() {
    return mud_version_major + "." + mud_version_minor + "." + mud_version_patch;
}