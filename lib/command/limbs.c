#include <command.h>

int query_padding(mapping body, string* limbs);
string query_color_health(float c, float m);

int main(string str) {
    object tp = this_player();
    mapping body = tp->query_body();
    string* limbs = sort_array(tp->query_limbs(), (: strcmp($1, $2) :));
    int pad = query_padding(body, limbs);

    write("Anatomy report: \n");

    foreach(string limb in limbs) {
        object* wielded = tp->query_worn(limb);
        string status = body[limb]["severed"]? "%^RED%^severed%^RESET%^":"intact";
        float chp = body[limb]["current_hp"];
        float mhp = body[limb]["max_hp"];
        string wielding = sizeof(wielded)? "%^GREEN%^" + list_strings(wielded->query_short())+"%^RESET%^" : "";
        write(sprintf("%-15s %-7s %s[%-:*.1f / %:*.1f]%%^RESET%%^ %s\n", limb, status, query_color_health(chp, mhp), pad+1, chp, pad+1, mhp, wielding));
    }
    return 1;
}

string query_color_health(float c, float m) {
    float percentof = percent(c, m);
    if (percentof > 75.0) {
        return "%^GREEN%^";
    }
    if (percentof > 50.0) {
        return "%#de6b2d%#";
    }
    if (percentof > 25.0) {
        return "%^YELLOW%^";
    }
    else {
        return "%^RED%^";
    }
}

int query_padding(mapping body, string* limbs) {
    int pad = 0;

    foreach(string limb in limbs) {
        float maxhp = body[limb]["max_hp"];
        int tmp = 0;
        while ((maxhp / 10) > 0.01) {
            tmp++;
            maxhp = maxhp/10;
            if (tmp > pad) {
                pad = tmp;
            }
        }
    }

    return pad;
}