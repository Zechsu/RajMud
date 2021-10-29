#include <command.h>

int main (string str) {
    string file;
    mixed result;
    string* words;
    int size;
    if (!str) {
        return notify_fail("Usage: cat <file name>\n");
    }
    if (str[0] == '/') {
        file = str;
    }
    else {
        file = TP()->query_cwd() + str;
    }

    if (file_size(file) == -2 || file_size(file) == -1) {
        return notify_fail("That is a directory or does not exist or is not readable.\n");
    }
    result = read_file(file);
    words = explode(result + "%#", "%#");
    size = sizeof(words);
    while (size--) {
        int* rgbs = TERM_D->html_color(words[size]);
        string old = words[size];
        if (sizeof(rgbs) == 3) {
            words[size] = rgb(rgbs[0], rgbs[1], rgbs[2]) + old + white();
        }
    }
    result = implode(words, "");
    if (stringp(result)) {
        tell_object(TP(), result + "\n");
    }
    return 1;
}
