// Author: David Malášek

#include "../include/file.h"

void print_options()
{
    printf("\n\033[1;34mOPTIONS\033[0m\n\n");
    printf("1. Add vehicle \n");
    printf("2. Remove vehicle \n");
    printf("3. Sort \n");
    printf("4. Info \n");
    printf("5. Show all \n");
    printf("6. Add random \n");
    printf("7. Search \n");
    printf("0. Quit \n");
    printf("\nSelect option: ");
}

void execute_option(int option_num)
{
    switch (option_num) {
        case 1:
            add_vehicle();
            break;
        case 2:
            remove_vehicle();
            break;
        case 3:
            sort_registry();
            break;
        case 6:
            add_random_vehicle();
            break;
        case 4:
            show_info_one_vehicle();
            break;
        case 5:
            print_registry(0, count_lines());
            break;
        default:
            fancy_print("Invalid option.", RED);
            break;
    }
}

int main()
{
    int selected_option;

    do {
        print_options();
        selected_option = read_int();
        if (selected_option != 0)
            execute_option(selected_option);
    } while (selected_option != 0);

    return 0;
}