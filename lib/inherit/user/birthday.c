#include <globals.h>
#include <date.h>

private class Date_t birthday;

void create() {
    if (!birthday || birthday == 0) {
        birthday = copy(NATURE_D->query_date());
    }
}

class Date_t query_birthday() {
    return birthday;
}

void set_birthday_ints(int hour, int day, int week, int month, int year) {
    birthday->hour = hour;
    birthday->day = day;
    birthday->week = week;
    birthday->month = month;
    birthday->year = year;
}

void set_birthday(class Date_t date) {
    birthday = date;
}