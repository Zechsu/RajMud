#include <command.h>

int
main(string arg)
{
    object *list = users();
    int j;

    printf("/-------------------------------------\\\n"
           "| Players online %d                    |\n" +
           ">-------------------------------------<\n",
           sizeof(list));
    for (j = 0; j < sizeof(list); j++) {
        printf("| %35-s |\n", list[j]->query_name());
    }
    printf("\\-------------------------------------/\n");
    return 1;
}
