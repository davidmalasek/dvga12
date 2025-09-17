// Author: David Malášek

#include "../include/file.h"

void print_options()
{
    fancy_print("OPTIONS", BLUE);
    printf("\n1. Add vehicle \n");
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
            if (add_vehicle())
                fancy_print("✅ Vehicle was succesfully added.", 0);
            break;
        case 2:
            if (remove_vehicle())
                fancy_print("✅ Vehicle was succesfully removed.", 0);
            break;
        case 3:
            if (sort_registry())
                fancy_print("✅ Registry was succesfully sorted.", 0);
            break;
        case 4:
            show_info_one_vehicle();
            break;
        case 5:
            print_registry(0, count_lines());
            break;
        case 6:
            if (add_random_vehicle()) {
                fancy_print("✅ Following random generated car was added:", 0);
                print_registry(count_lines() - 1, 1);
            }
            break;
        case 7:
            search_for_owner();
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