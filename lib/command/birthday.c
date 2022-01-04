#include <command.h>
#include <date.h>

int main(string arg) {
    class Date_t date = TP->query_birthday();
    int age = NATURE_D->query_year() - date->year;
    write(sprintf("%s the %s, Year %d\n", NATURE_D->query_month_name(date->month), query_nth(date->day), date->year));
    write("You are " + age + " years old.\n");
    return 1;
}