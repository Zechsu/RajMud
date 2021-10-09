#include <command.h>

string help() {
    return "Usage: put <item> in <container>\n";
}

int main(string str) {
    object tp = this_player();
    mixed item, container;

    if (!str) {
        return notify_fail(help());
    }

    if (sscanf(str, "%s in %s", item, container) == 2) {
        if (!item = present(item)) {
            return notify_fail(help());
        }
        if (!container = present(container)) {
            return notify_fail(help());
        }
        if (container->is_container()) {
            item->event_put(tp, container);
            write("You put " + item->query_short() + " in " + container->query_short() + ".\n");
            return 1;
        }
    }

    return 1;
}