#include <rgb.h>

int main(string arg) {
    string* colors;
    int* color1, *color2;
    int new_r, new_g, new_b;
    class RGB_t mixture;
    if (!arg) {
        return notify_fail("Need at least 2 colors to mix\n");
    }
    
    colors = explode(arg, " ");
    if (sizeof(colors) < 2) {
        return notify_fail("Need at least 2 colors to mix\n");
    }
    // color1 = map_array(explode(colors[0], ","), (: to_int($1) :));
    // color2 = map_array(explode(colors[1], ","), (: to_int($1) :));
    // new_r = (color1[0] + color2[0]) / 2;
    // new_g = (color1[1] + color2[1]) / 2;
    // new_b = (color1[2] + color2[2]) / 2;
    mixture = blend(colors);
    write(rgb(mixture->r, mixture->g, mixture->b) + "The quick brown fox jumps over the lazy dog%^RESET%^\n");
    return 1;
}