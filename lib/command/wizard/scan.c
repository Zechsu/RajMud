#include <command.h>

void print_children(object ob, int indent);

int main(string arg) {
    object env = environment(this_player());
    object* inv = all_inventory(env);

    tell_object(this_player(), sprintf(" o %s (%s)\n", env->query_short(), file_name(env)));
    foreach(object ob in inv) {
        print_children(ob, 1);
    }
    return 1;
}

void print_children(object ob, int indent) {
    tell_object(this_player(), sprintf(" |%*'-'s %s (%s)\n", indent, "", ob->query_short(), file_name(ob)));
    foreach (object obj in all_inventory(ob)) {
        print_children(obj, indent + 2);
    }
}