#include <globals.h>
#include <date.h>
#include <nature.h>

private string* month_names = ({});
private class Date_t date;

void init_month_names();
void save_me();

void create() {
    if (clonep(this_object())) {
        return;
    }
    if (!restore_object(NATURE_SAVE)) {
        date = new(class Date_t);
    }
    init_month_names();
}

void init_month_names() {
    month_names = ({MONTH_ONE, MONTH_TWO, MONTH_THREE, MONTH_FOUR, MONTH_FIVE, 
                    MONTH_SIX, MONTH_SEVEN, MONTH_EIGHT, MONTH_NINE, MONTH_TEN, 
                    MONTH_ELEVEN, MONTH_TWELVE, MONTH_THIRTEEN, MONTH_FOURTEEN});
}

void increment_day() {
    date->day++;
    save_me();
}

void increment_month() {
    date->month++;
    save_me();
}

class Date_t query_date() {
    return date;
}

void save_me() {
    save_object(NATURE_SAVE);
}

string query_month_name(int month_n) {
    if (month_n >= 1 && month_n <= 14) {
        return month_names[month_n-1];
    }
    debug_message("query_month_name recieved invalid month number: " + month_n);
    return 0;
}