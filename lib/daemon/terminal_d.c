#include <globals.h>

#define ANSI(p) sprintf("%c["+(p)+"m", 27)
#define ESC(p) sprintf("%c"+(p), 27)

mapping data;

varargs string parse_html(string msg, int flag);

void create() {
    data = ([
        "RESET":ANSI("0;37;40"), "BOLD":ANSI(1), "FLASH":ANSI(5),
        "BLACK":ANSI(30), "RED":ANSI(31), "GREEN":ANSI(32),
        "YELLOW": ANSI(33), "BLUE": ANSI(34), "CYAN":ANSI(36),
        "MAGENTA":ANSI(35), "BLACK":ANSI(30), "WHITE": ANSI(37),
        "B_RED":ANSI(41), "B_GREEN":ANSI(42), "B_ORANGE":ANSI(43),
        "B_YELLOW": ANSI(43), "B_BLUE":ANSI(44),
        "B_CYAN":ANSI(46), "B_BLACK":ANSI(40), "B_WHITE": ANSI(47),
        "B_MAGENTA":ANSI(45), "STATUS":"", "WINDOW":"", "INITTERM":ESC("[H")+ESC("[2J"),
        "ENDTERM":"", "FRTOP" : ESC("[2;25r"), "FRBOTTOM" : ESC("[1;24r"),
        "UNFR" : ESC("[r"), "SAVEC" : ESC("[s"), "RESTC" : ESC("[u"),
        "HOMEC" : ESC("[H"), "CLEAR" : ESC("[2J"), "ER_SOL" : ESC("[1k"),
        "ER_EOL" : ESC("[K"), "ER_LINE" : ESC("[2K"), "ER_DOWN" : ESC("[J"),
        "ER_UP" : ESC("[1J")
    ]);
}

mapping colors() {
    return data;
}

int is_color(string col) {
    if (data[col]) {
        return 1;
    }
    else {
        return 0;
    }
}

varargs string parse_pinkfish(string msg, int flag)
{

    string *words;
    int size;

    words = explode(msg + "%^", "%^");
    size = sizeof(words);

    if(flag)
    {
        while(size--)
        {
            if(data[words[size]])
            {
                words[size] = "";
            }
        }  
    }
    else
    {
        while(size--)
        {
            if(data[words[size]])
            {
                words[size] = data[words[size]];
            }
        }
    }
    
    msg = implode(words, "");
    
    msg = parse_html(msg, flag);
    
    return msg;
}

mixed html_color(string str) {
    string string_r, string_g, string_b;
    int r, g, b;

    if(!str)
    {
        return "";
    }
    
    str = upper_case(str);
    if(!regexp(str, "[A-F0-9][A-F0-9][A-F0-9][A-F0-9][A-F0-9][A-F0-9]"))
    {
        return "";
    }

    string_r = str[0..1];
    string_g = str[2..3];
    string_b = str[4..5];

    if(sscanf(string_r, "%x", r) != 1) return "";
    if(sscanf(string_g, "%x", g) != 1) return "";
    if(sscanf(string_b, "%x", b) != 1) return "";

    return ({ r, g, b });
}

varargs string parse_html(string msg, int flag)
{
    string *words;
    int size;

    words = explode(msg + "%#", "%#");
    size = sizeof(words);

    if (flag) {
        while(size--) {
            if (regexp(upper_case(words[size]), "[A-F0-9][A-F0-9][A-F0-9][A-F0-9][A-F0-9][A-F0-9]")) {
                words[size] = "";
            }
        }
    }
    else {
        while(size--)
        {
            int* rgbs = html_color(words[size]);
            if (sizeof(rgbs) == 3) {
                words[size] = rgb(rgbs[0], rgbs[1], rgbs[2]);
            }
        }
    }

    msg = implode(words, "");

    return msg;
}