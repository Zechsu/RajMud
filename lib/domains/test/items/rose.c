#include <globals.h>

inherit LIB_ITEM;

private string* rose_colors = ({"%#eb0909%#", "%#f1ebeb%#", "%#e88c6e%#", "%#ec9755%#", "%#ec5575%#", "%#ecd355%#"});
private string col = element_of(rose_colors);

void create() {
    ::create();
    set_short(col + "rose%^RESET%^");
    set_long("A beautiful " + col + "flower%^RESET%^. Careful of its thorns!");
    set_ids(({"rose"}));
}

mixed event_recieved(object who) {
    if (random(5) == 1) {
        write("You prick your finger on the thorns!\n");
    }
}
