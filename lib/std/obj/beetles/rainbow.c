inherit "std/obj/beetle";

int count = 0;

string do_rainbow_name(string sh);

void create() {
    ::create();
    set_short(do_rainbow_name("rainbow beetle"));
    set_ids(({"rainbow", "rainbow", "beetle"}));
}

string get_rainbow() {
    switch (count) {
        case 0:
            count++;
            return rgb(148, 0, 211);
        case 1:
            count++;
            return rgb(75, 0, 130);
        case 2:
            count++;
            return rgb(0, 0, 255);
        case 3:
            count++;
            return rgb(0, 255, 0);
        case 4:
            count++;
            return rgb(255, 255, 0);
        case 5:
            count++;
            return rgb(255, 127, 0);
        case 6:
            count = 0;
            return rgb(255, 0, 0);
    }
}

string do_rainbow_name(string sh) {
    string str = "";
    for (int i = 0; i < sizeof(sh); i++) {
        str += get_rainbow() + sh[i..i];
    }
    return str + white();
}
