#include <globals.h>

#define ANSI(p) sprintf("%c["+(p)+"m", 27)
#define ESC(p) sprintf("%c"+(p), 27)

mapping colors;

void create() {
    colors = ([ "RESET":ANSI("0"), "BOLD":ANSI(1), "FLASH":ANSI(5),
    "BLACK":ANSI(30), "RED":ANSI(31), "GREEN":ANSI(32),
    "ORANGE":ANSI(33),     "YELLOW":ANSI(1)+ANSI(33), "BLUE": ANSI(34),
    "CYAN":ANSI(36), "MAGENTA":ANSI(35), "BLACK":ANSI(30),
    "WHITE": ANSI(37), "B_RED":ANSI(41), "B_GREEN":ANSI(42),
    "B_ORANGE":ANSI(43), "B_YELLOW":ANSI(1)+ANSI(43), "B_BLUE":ANSI(44),
    "B_CYAN":ANSI(46), "B_BLACK":ANSI(40), "B_WHITE": ANSI(47),
    "CLEARLINE":ESC("[L")+ESC("[G"), "B_MAGENTA":ANSI(45), "STATUS":"",
    "WINDOW":"", "INITTERM":ESC("[H")+ESC("[2J"), "ENDTERM":"" ]);
}

string no_colors(string str) {
    return terminal_colour(str,colors);
}

string no_colours(string str) {
    return no_colors(str);
}

mapping colors() {
    return colors;
}