#include <command.h>

string help() {
    return "Usage: put <item> in <container>\n";
}

int main(string str) {
    mixed item, container, res;
    object iob, cob;
    object tp = TP;

    if (!str) {
        return notify_fail(help());
    }

    if (sscanf(str, "%s in %s", item, container) == 2) {
        iob = present(item, tp);
        if (!iob) iob = present(item, ENV(tp));
        if (!iob) {
            return notify_fail(help());
        }
        cob = present(container, tp);
        if (!cob) cob = present(container, ENV(tp));
        if (!cob) {
            return notify_fail(help());
        }
        if (cob->is_container()) {
            return cob->event_recieve_item(iob, tp);
        }
    }

    return 1;
}