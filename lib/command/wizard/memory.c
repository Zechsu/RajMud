#include <command.h>

int main(string obj) {
    object ob;

    if (obj) {
        ob = present(obj);
        if (!ob) ob = present(obj, ENV(TP));
        if (!ob) ob = find_object(obj);
        if (!ob) return notify_fail("Couldn't find that object.\n");
        write(file_name(ob) + " = " + memory_info(ob) + " bytes\n");
        return 1;
    }
    write("RajMUD is using " + memory_info()/1024 + " kilobytes.\n");
    return 1;
}
