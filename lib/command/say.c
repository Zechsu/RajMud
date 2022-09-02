#include <command.h>
#include <daemons.h>

#ifdef __NO_ENVIRONMENT__
#define say(x) shout(x)
#endif

int main(string arg)
{
    string name = (string)previous_object()->query_name();
    if (!arg || trim(arg) == "") {
        return notify_fail("Say what?\n");
    }
    if (SECURE_D->query_wizard(name)) {
        int length = strlen(arg);
        int uneven = 0;
        string* grad1;
        string* grad2;
        if (length <= 3) {
            arg = "%^BOLD%^" + alternate_colors(arg, ({rgb(237, 224, 126), rgb(217, 237, 126)}));
        }
        else {
            grad1 = color_gradient(({237, 224, 126}), ({217, 237, 126}), length/2);
            if (length % 2 != 0) {
                uneven = 1;
            }
            if (uneven == 1) {
                grad2 = color_gradient(({217, 237, 126}), ({237, 224, 126}), (length/2) + 1);
            }
            else {
                grad2 = color_gradient(({217, 237, 126}), ({237, 224, 126}), length/2);
            }
            arg = "%^BOLD%^" + apply_gradient(arg, grad1+grad2);
        }

        write("You say " + "\"" + arg + "\""  + "\n");
        say(name + " says " + arg + "\"" +arg + "\"" +"\n");
    }
    else {
        write("You say \"" + sprintf("%c["+(1)+"m", 27) + arg +sprintf("%c["+(0)+"m", 27)+"\"\n");
        say(name + " says \"" + arg +"\"\n");
    }

    return 1;
}

string help() {
    return "Talk to anyone in the same room as you\nUsage: say <text>\n"; 
}
