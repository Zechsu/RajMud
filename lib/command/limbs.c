#include <command.h>
#include <flags/limbs_flags.h>

int query_padding(mapping body, string* limbs);
string query_color_health(float c, float m, int pad);
string query_status(mapping limb);

int main(string str) {
    object tp = this_player();
    mapping body = tp->query_body();
    string* limbs = sort_array(tp->query_limbs(), (: strcmp($1, $2) :));
    int pad = query_padding(body, limbs);

    write("Anatomy report: \n");

    foreach(string limb in limbs) {
        object* wielded = tp->query_worn(limb);
        string status = query_status(body[limb]);
        float chp = body[limb]["current_hp"];
        float mhp = body[limb]["max_hp"];
        string wielding = sizeof(wielded)? "%^GREEN%^" + list_strings(wielded->query_short())+"%^RESET%^" : "";
        string hp = query_color_health(chp, mhp, pad);
        write(sprintf("%-15s %-8s %-8s %s\n", limb, status, hp, wielding));
    }
    return 1;
}

string query_status(mapping limb) {
    if (limb["flags"] & LIMB_SEVERED) {
        return "%^RED%^severed %^RESET%^";
    }
    if (limb["current_hp"] <= -0.0) {
        return "%^CYAN%^disabled%^RESET%^";
    }
    return "%^GREEN%^intact  %^RESET%^";
}

string query_color_health(float current_hp, float max_hp, int pad) {
    float percentof = percent(current_hp, max_hp);
    string hp = sprintf("[%-:*.1f / %:*.1f]", pad+1, c, pad+1, m);
    if (percentof > 75.0) {
        return "%^GREEN%^" + hp + "%^RESET%^";
    }
    if (percentof > 50.0) {
        return "%#de6b2d%#" + hp + "%^RESET%^";
    }
    if (percentof > 25.0) {
        return "%^YELLOW%^" + hp + "%^RESET%^";
    }
    else {
        return "%^RED%^" + hp + "%^RESET%^";
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