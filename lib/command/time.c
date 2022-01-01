#include <command.h>
#include <date.h>

int main(string arg) {
    class Date_t date = NATURE_D->query_date();
    write(sprintf("It is %s the %s, Year %d\n", NATURE_D->query_month_name(date->month), query_nth(date->day), date->year));
    return 1;
}