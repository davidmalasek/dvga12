// Author: David Malášek

#include "../include/main.h"
#include "../include/file.h"

void print_options()
{
    printf("1. Add vehicle \n");
    printf("2. Remove vehicle \n");
    printf("3. Sort \n");
    printf("4. Info \n");
    printf("5. Show all \n");
    printf("6. Add random \n");
    printf("7. Search \n");
    printf("0. Quit \n");
}

void execute_option(int option_num)
{
    switch (option_num) {
        case 1:

    }
}

int main()
{
    int selected_option;

    while (1) {
        print_options();
        selected_option = read_int();
        if (selected_option == 0)
            break;
        else
            execute_option(selected_option);
    }
    return 0;
}