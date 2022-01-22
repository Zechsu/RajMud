#include <globals.h>
#include <date.h>
#include <nature.h>

// 2 minutes is an in-game hour
#define TICK 120

private nosave string* month_names = ({});
private nosave int* month_days = ({});
private class Date_t date;

void init_months();
void increment_hour();
void increment_day();
void increment_month();
void increment_year();
void save_me();

void create() {
    if (clonep(this_object())) {
        return;
    }
    if (!restore_object(NATURE_SAVE)) {
        date = new(class Date_t);
        date->day = 1;
        date->month = 1;
        date->week = 1;
    }
    init_months();
    call_out("tick_tock", 5);
}

void tick_tock() {
    increment_hour();
    call_out("tick_tock", TICK);
}

void init_months() {
    month_names = ({MONTH_ONE, MONTH_TWO, MONTH_THREE, MONTH_FOUR, MONTH_FIVE, 
                    MONTH_SIX, MONTH_SEVEN, MONTH_EIGHT, MONTH_NINE, MONTH_TEN, 
                    MONTH_ELEVEN, MONTH_TWELVE, MONTH_THIRTEEN, MONTH_FOURTEEN});
    month_days = ({35, 35, 35, 34, 33, 34, 36, 34, 34, 34, 35, 34, 36, 27});
}

void increment_hour() {
    date->hour++;
    if (date->hour >= 24) {
        date->hour = 0;
        increment_day();
    }
    save_me();
}

void increment_day() {
    date->day++;
    if (date->day % 6 == 0) {
        date->week++;
    }
    if (date->day >= month_days[date->month-1]) {
        date->day = 1;
        increment_month();
    }
    save_me();
}

void increment_month() {
    date->month++;
    if (date->month == 14) {
        date->month = 1;
        increment_year();
    }
    save_me();
}

void increment_year() {
    date->year++;
    date->week = 1;
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

int query_year() {
    return date->year;
}

int query_day() {
    return date->day;
}

int query_month() {
    return date->month;
}

int query_hour() {
    return date->hour;
}