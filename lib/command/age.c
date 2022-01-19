#include <command.h>
#include <date.h>

int main(string arg) {
    class Date_t date = TP->query_birthday();
    int years = NATURE_D->query_year() - date->year;
    int months = NATURE_D->query_month() - date->month;
    int days = (NATURE_D->query_day() - date->day) % 476;
    write(sprintf("Your birthday is %s the %s, Year %d\n", NATURE_D->query_month_name(date->month), query_nth(date->day), date->year));
    write("You are " + years + " years, " + months + " months and " + days + " days old.\n");
    return 1;
}