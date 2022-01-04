#include <command.h>
#include <date.h>

int main(string arg) {
    class Date_t date = NATURE_D->query_date();
    if (date->hour == 12) {
        write("It's 12 PM\n");
    }
    else if (date->hour == 24) {
        write("It's 12 AM\n");
    }
    else if (date->hour > 12) {
        write(sprintf("It's %d %s\n", date->hour%12, "PM"));
    }
    else {
        write(sprintf("It's %d %s\n", date->hour, "AM"));
    }
    write(sprintf("%s the %s, Year %d\n", NATURE_D->query_month_name(date->month), query_nth(date->day), date->year));
    return 1;
}