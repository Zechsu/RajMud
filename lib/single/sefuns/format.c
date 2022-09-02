// Everything stolen from Diavolo @ Nightmare Residium

private nosave mapping __Border = ([
    "utf-8": ([
        // lines
        "h": "─",
        "v": "│",
        // corners
        "tl": "┌",
        "tr": "┐",
        "br": "┘",
        "bl": "└",
        // joints
        "t": "┬",
        "b": "┴",
        "l": "├",
        "r": "┤",
    ]),
    "US-ASCII": ([
        // lines
        "h": "-",
        "v": "|",
        // corners
        "tl": ".",
        "tr": ".",
        "br": "'",
        "bl": "'",
        // joints
        "t": "-",
        "b": "-",
        "l": "|",
        "r": "|",
    ]),
]);

string remove_color(string str);
string apply_gradient (string text, string *gradient);
string *color_gradient (int *color1, int *color2, int steps);

varargs string format_page (string *items, int columns, int pad, int center) {
    int width, w, i, j, n, r;
    string *rows = ({});

    if (!arrayp(items) || !sizeof(items)) error("Bad argument 1 to format->format_page");

    if (!columns) columns = 2;
    width = 80 - pad * 2;
    w = width / columns; // width of column
    n = sizeof(items); // number of columns
    r = width - (w * columns); // remainder
    items = map(items, (: "" + $1 :));

    for (i = 0; i < n; i += columns) {
        string row = "";
        for (j = 0; j < columns; j ++) {
            string tmp;
            if (i + j >= n) { // ran out of columns to fill final row
                row += sprintf("%' '"+sprintf("%d", w*(columns-j))+"s", " ");
                break;
            }
            // check text length without ANSI color
            if (sizeof(tmp = remove_color(items[i + j])) > w) {
                // use stripped text when its longer than w
                row += tmp[0..w-1];
            } else {
                // account for any color codes in the text
                int diff = sizeof(items[i+j]) - sizeof(tmp);

                if (center) {
                    row += sprintf("%|"+sprintf("%d", w+diff)+"s", ""+items[i + j]);
                } else {
                    row += sprintf("%-"+sprintf("%d", w+diff)+"s", ""+items[i + j]);
                }

                // when color codes present and we're not displaying a RESET, add one
                if (diff > 0 && items[i + j][<9..] != "%^RESET%^") row += "%^RESET%^";
            }
        }
        if (r) row += sprintf("%' '"+sprintf("%d", r)+"s", "");
        rows += ({ row });
    }
    return implode(rows, "\n");
}

string *format_border (mapping data) {
    string *lines = ({ }), line, *linesBody = ({ });

    int fTitle = !undefinedp(data["title"]);
    int fSubtitle = !undefinedp(data["subtitle"]);
    int fHeader = !undefinedp(data["header"]);
    int fBody = !undefinedp(data["body"]);
    int fFooter = !undefinedp(data["footer"]);

    // If not on screenreader
    if (1) {
        mapping b = __Border[query_encoding()];
        int width, ansi, n;
        string *colors, *colors2, *colorsBody, *colorsBody2;
        int *c1, *c2;

        ansi = 1;
        width = 80;;
        n = 0;

        if (ansi) {
            c1 = ({ 191, 63, 191 }); // pink
            c2 = ({ 63, 191, 191 }); // cyan
            colors = color_gradient(c1, c2, width);
            colors2 = ({ });
            for (int i = sizeof(colors)-1; i >= 0; i --) {
                colors2 += ({ colors[i] });
            }
        } else {
            colors = allocate(width, "");
            colors2 = colors;
        }

        if (fTitle) {
            int titleLength = 0;

            // Title Line 1
            line = "   " + b["tl"] + sprintf("%'"+b["h"]+"'"+sprintf("%d", 2 + strlen(data["title"]) + (fSubtitle ? 2 + strlen(data["subtitle"]) : 0))+"s", "") + b["tr"];
            if (ansi) {
                line = apply_gradient(line, colors);
            }
            lines += ({ line });

            // Title Line 2
            line = b["tl"] + (fHeader ? b["t"] : b["h"]) + b["h"];
            line += b["r"] + " " + data["title"];
            n += 5 + strlen(data["title"]);
            if (fSubtitle) {
                line += ": " + data["subtitle"];
                n += 2 + strlen(data["subtitle"]);
            }
            titleLength = n;
            line += " " + b["l"] + b["h"];
            n += 3;
            line += sprintf("%'"+b["h"]+"'"+sprintf("%d", width-2-n)+"s", "");
            line += (fHeader ? b["t"] : b["h"]) + b["tr"];
            if (ansi) {
                line = apply_gradient(line[0..4], colors[0..4]) + "\e[0;37;40;1m" + replace_string(line[5..titleLength-1], ":", ":\e[22m") + apply_gradient(line[titleLength..], colors[titleLength..]);
            }
            lines += ({ line });

            // Title Line 3
            line = b["v"] + (fHeader ? b["v"] : " ") + " ";
            line += b["bl"] + sprintf("%'"+b["h"]+"'"+sprintf("%d", 2 + strlen(data["title"]) + (data["subtitle"] ? 2 + strlen(data["subtitle"]) : 0))+"s", "") + b["br"];
            line += sprintf("%' '"+sprintf("%d", width-1-n)+"s", "");
            line += (fHeader ? b["v"] : " ") + b["v"];
            if (ansi) {
                line = apply_gradient(line, colors);
            }
            lines += ({ line });

        } else { // no title
            line = b["tl"] + (fHeader ? b["t"] : b["h"]) + sprintf("%'"+b["h"]+"'"+sprintf("%d", width-4)+"s", "") + (fHeader ? b["t"] : b["h"]) + b["tr"];
            if (ansi) {
                line = apply_gradient(line, colors);
            }
            lines += ({ line });
        }

        if (fHeader) {
            string format;
            int center = (data["header"]["align"] == "center");
            string left, right;

            left = b["v"] + b["v"];
            right = b["v"] + b["v"];
            if (ansi) {
                left = apply_gradient(left, colors[0..1]);
                right = apply_gradient(right, colors[<2..<1]);
            }
            // Header header
            if (stringp(data["header"]["header"])) {
                line = left + "  " + (ansi?"\e[0;37;40;1m":"") + data["header"]["header"] + (ansi?"\e[22m":"") + sprintf("%' '"+sprintf("%d", width - 8 - strlen(data["header"]["header"]))+"s", "") + "  " + right;
                lines += ({ line });
            } else if (arrayp(data["header"]["header"])) {
                if (!data["header"]["columns"]) {
                    data["header"]["columns"] = 2;
                }
                if (sizeof(data["header"]["header"]) > data["header"]["columns"]) {
                    data["header"]["header"] = data["header"]["header"][0..data["header"]["columns"]-1];
                }
                line = left + "  " + (ansi?"\e[0;37;40;1m":"") + format_page(data["header"]["header"], data["header"]["columns"], 4, center) + (ansi?"\e[22m":"") + "  " + right;
                lines += ({ line });
            }
            // Header lines
            format = sizeof(data["header"]["items"]) > 0 ? format_page(data["header"]["items"], data["header"]["columns"], 4, center) : "";
            foreach (string l in explode(format, "\n")) {
                line = left + "  " + l + "  " + right;
                lines += ({ line });
            }
            // Header bottom line
            line = b["v"] + b["bl"] + sprintf("%'"+b["h"]+"'"+sprintf("%d", width - 4)+"s", "") + b["br"] + b["v"];
            if (ansi) {
                line = apply_gradient(line, colors);
            }
            lines += ({ line });
        }

        if (fBody && mapp(data["body"])) {
            data["body"] = ({ data["body"] });
        }
        if (fBody && arrayp(data["body"])) {
            // Body top line
            line = sprintf("%' '"+sprintf("%d", width - 2)+"s", "");
            if (ansi) {
                line = apply_gradient(line, colors);
            }
            linesBody += ({ line });
            foreach (mapping child in data["body"]) {
                string format;
                int center = (child["align"] == "center");

                // Body child header
                if (stringp(child["header"])) {
                    line = "   " + (ansi?"\e[0;37;40;1m":"") + child["header"] + (ansi?"\e[22m":"") + sprintf("%' '"+sprintf("%d", width - 8 - strlen(child["header"]))+"s", "") + "   ";
                    linesBody += ({ line });
                } else if (arrayp(child["header"])) {
                    if (!child["columns"]) {
                        child["columns"] = 2;
                    }
                    if (sizeof(child["header"]) > child["columns"]) {
                        child["header"] = child["header"][0..child["columns"]-1];
                    }
                    line = "   " + (ansi?"\e[0;37;40;1m":"") + format_page(child["header"], child["columns"], 4, center) + (ansi?"\e[22m":"") + "   ";
                    linesBody += ({ line });
                }
                // Body child lines
                format = sizeof(child["items"]) > 0 ? format_page(child["items"], child["columns"], 4, center) : "";
                foreach (string l in explode(format, "\n")) {
                    line = "   " + l + "   ";
                    linesBody += ({ line });
                }
                // Body child bottom line
                line = sprintf("%' '"+sprintf("%d", width - 2)+"s", "");
                linesBody += ({ line });
            }
            if (ansi) {
                string left, right;
                colorsBody = color_gradient(c1, c2, sizeof(linesBody) + 2);
                colorsBody = colorsBody[1..<2];
                colorsBody2 = ({ });
                for (int i = sizeof(colorsBody)-1; i >= 0; i --) {
                    colorsBody2 += ({ colorsBody[i] });
                }
                for (int i = sizeof(linesBody)-1; i >= 0; i --) {
                    left = apply_gradient(b["v"], ({ colorsBody[i] }));
                    right = apply_gradient(b["v"], ({ colorsBody2[i] }));
                    linesBody[i] = left + linesBody[i] + right;
                }
            } else {
                for (int i = sizeof(linesBody)-1; i >= 0; i --) {
                    linesBody[i] = b["v"] + linesBody[i] + b["v"];
                }
            }

            lines += linesBody;
        }

        if (fFooter) {
            string format;
            int center = (data["footer"]["align"] == "center");
            string left, right;

            left = b["v"] + b["v"];
            right = b["v"] + b["v"];
            if (ansi) {
                left = apply_gradient(left, colors2[0..1]);
                right = apply_gradient(right, colors2[<2..<1]);
            }

            // Footer top line
            line = b["v"] + b["tl"] + sprintf("%'"+b["h"]+"'"+sprintf("%d", width - 4)+"s", "") + b["tr"] + b["v"];
            if (ansi) {
                line = apply_gradient(line, colors2);
            }
            lines += ({ line });
            // Footer header
            if (stringp(data["footer"]["header"])) {
                line = left + "  " + (ansi?"\e[0;37;40;1m":"") + data["footer"]["header"] + (ansi?"\e[22m":"") + sprintf("%' '"+sprintf("%d", width - 8 - strlen(data["footer"]["header"]))+"s", "") + "  " + right;
                lines += ({ line });
            } else if (arrayp(data["footer"]["header"])) {
                if (!data["footer"]["columns"]) {
                    data["footer"]["columns"] = 2;
                }
                if (sizeof(data["footer"]["header"]) > data["footer"]["columns"]) {
                    data["footer"]["header"] = data["footer"]["header"][0..data["footer"]["columns"]-1];
                }
                line = left + "  " + (ansi?"\e[0;37;40;1m":"") + format_page(data["footer"]["header"], data["footer"]["columns"], 4, center) + (ansi?"\e[22m":"") + "  " + right;
                lines += ({ line });
            }
            // Footer lines
            format = sizeof(data["footer"]["items"]) > 0 ? format_page(data["footer"]["items"], data["footer"]["columns"], 4, center) : "";
            foreach (string l in explode(format, "\n")) {
                line = left + "  " + l + "  " + right;
                lines += ({ line });
            }
            // Border Bottom line
            line = b["bl"] + b["b"] + sprintf("%'"+b["h"]+"'"+sprintf("%d", width - 4)+"s", "") + b["b"] + b["br"];
            if (ansi) {
                line = apply_gradient(line, colors2);
            }
            lines += ({ line });
        } else {
            // Border Bottom line
            line = b["bl"] + sprintf("%'"+b["h"]+"'"+sprintf("%d", width - 2)+"s", "") + b["br"];
            if (ansi) {
                line = apply_gradient(line, colors2);
            }
            lines += ({ line });
        }
    } else { // screenreader
        if (fTitle) {
            lines += ({ data["title"] + (fSubtitle ? ": " + data["subtitle"] : "") });
            lines += ({ "" });
        }
        if (fHeader) {
            foreach (string item in data["header"]["items"]) {
                lines += ({ item });
            }
            lines += ({ "" });
        }
        if (fBody && mapp(data["body"])) {
            data["body"] = ({ data["body"] });
        }
        if (fBody && arrayp(data["body"])) {
            foreach (mapping child in data["body"]) {
                if (child["header"]) {
                    lines += ({ child["header"] });
                }
                foreach (string item in child["items"]) {
                    lines += ({ item });
                }
            }
        }
        if (fFooter) {
            lines += ({ "" });
            foreach (string item in data["footer"]["items"]) {
                lines += ({ item });
            }
        }
    }

    return lines;
}