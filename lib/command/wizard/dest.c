#include <command.h>

int main(string arg)
{
    object tp = this_player();
    object* inv = all_inventory(environment(tp));
	object target;

    if (!arg) {
        return notify_fail("usage: dest object\n");
    }
	
    target = present(arg, tp);
    if (!target) target = present(arg, ENV(tp));
	if (target) {
        if (target->is_prop()) {
            return notify_fail("Cannot dest a prop\n");
        }
		write("Destroyed " + target->query_short() + "\n");
		target->remove();
		return 1;
	}

    return notify_fail("Object not found.\n");
}
