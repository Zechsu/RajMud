#include <command.h>

#define F_FUNCTIONS     1 << 0
#define F_VARIABLES     1 << 1
#define F_FUNCTIONS_SIG 1 << 2

int flags = 0;

void print_examine(object obj);

int main(string arg) {
    object ob;
    string* cmd;
    flags = 0;
    if (!arg || trim(arg) == "") {
        return notify_fail("Examine what?\n");
    }
    if (lower_case(arg) == "here") {
        print_examine(environment(this_player()));
        return 1;
    }
    cmd = explode(arg, "-");
    arg = rtrim(cmd[0]);
    ob = present(arg, this_player());
    if (!ob) ob = present(arg, environment(this_player()));
    if (!ob) return notify_fail("Couldn't find object\n");

    foreach (string flag in cmd[1..]) {
        switch (trim(flag)) {
            case "f": {
                flags ^= F_FUNCTIONS;
                break;
            }
            case "v": {
                flags ^= F_VARIABLES;
                break;
            }
            case "f2": {
                flags ^= F_FUNCTIONS_SIG;
                break;
            }
        }
    }
    print_examine(ob);
    return 1;
}

void print_examine(object obj) {
    write(sprintf("%%^GREEN%%^%s\n", base_name(obj)));
    write(sprintf("Functions count: %d\n", sizeof(functions(obj))));
    write(sprintf("Variables count: %d\n", sizeof(variables(obj))));
    write(sprintf("Memory usage: %dKb\n%%^RESET%%^", memory_info(obj)/1024));
    if (flags & F_FUNCTIONS_SIG) {
        string* functs = functions(obj, 1);
        write("%^GREEN%^");
        foreach (string* function_sig in functs) {
            string ident = function_sig[0];
            string ret_type = function_sig[2];
            mixed par_count = function_sig[1];
            string* par_types;
            if (par_count) {
                par_types = ({});
                for (int i = 3; i < 3 + par_count; i++) {
                    par_types += ({function_sig[i]});
                }
            }
            write(sprintf("%s %s %s\n", ret_type, ident, "(" + implode(par_types, " ") + ")"));
        }
        write("%^RESET%^");
    }
    if (flags & F_FUNCTIONS) {
        string* funcs = functions(obj);
        write("%^GREEN%^");
        foreach (string fun in funcs) {
            write(fun + "\n");
        }
        write("%^RESET%^");
    }
    if (flags & F_VARIABLES) {
        string* vars = variables(obj);
        write("%^GREEN%^");
        foreach (string var in vars) {
            write(var + "\n");
        }
        write("%^RESET%^");
    }
}