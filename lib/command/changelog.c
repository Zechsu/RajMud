#include <command.h>
#include <daemons.h>

int main(string str) {
    if (str == "add") {
        if (SECURE_D->query_wizard(this_player()->query_name())) {
            tell_object(this_player(), "Summary: ");
            input_to("add_summary");
        }
        else {
            cat("changelog");
        }
    }
    else {
        cat("changelog");
    }
    return 1;
}

void add_summary(string summary)  {
    tell_object(this_player(), "Description: \n");
    input_to("add_description", 0, summary);
}

void add_description(string description, string summary) {
    tell_object(this_player(), "Version: \n");
    tell_object(this_player(), "major: X.x.x\n");
    tell_object(this_player(), "minor: x.X.x\n");
    tell_object(this_player(), "patch: x.x.X\n");
    input_to("add_version", 0, summary, description);
}

void add_version(string version, string summary, string description) {
    mapping entry = ([]);
    entry["summary"] = summary;
    entry["description"] = description;
    entry["version"] = version;
    CHANGELOG_D->add_entry(entry);
    tell_object(this_player(), "Added new entry #" + CHANGELOG_D->query_entries_count() + "\n");
}