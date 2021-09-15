#include <command.h>
#include <daemons.h>

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
    if (SECURE_D->query_wizard(name)) {
        write("You say \"" +sprintf("%c["+(1)+"m", 27)+sprintf("%c["+(33)+"m", 27) + arg + sprintf("%c["+(0)+"m", 27) + "\"\n");
        say(name + " says \"" +sprintf("%c["+(1)+"m", 27)+sprintf("%c["+(33)+"m", 27) + arg + sprintf("%c["+(0)+"m", 27) +"\"\n");
    }
    else {
        write("You say \"" + arg + "\"\n");
        say(name + " says \"" + arg +"\"\n");
    }

    return 1;
}

string help() {
    return "Talk to anyone in the same room as you\nUsage: say <text>\n"; 
}
