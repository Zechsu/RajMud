#include <command.h>

#ifdef __NO_ENVIRONMENT__
#define say(x) shout(x)
#endif

int main(string arg)
{
    string name = (string)previous_object()->query_name();
    if (!arg || trim(arg) == "") {
        write("Say what?\n");
	return 1;
    }
    write("You say \"" + arg + "\"\n");
    say(name
        + " says \"" +  arg + "\"\n");
    return 1;
}

string help() {
    return "Talk to anyone in the same room as you\nUsage: say <text>\n"; 
}
