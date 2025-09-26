// Author: David Malášek

#include "../include/file.h"

void print_options()
{
    fancy_print("OPTIONS", BLUE);
    printf("1. Add vehicle \n");
    printf("2. Remove vehicle \n");
    printf("3. Sort vehicles \n");
    printf("4. Info about vehicle \n");
    printf("5. Show all vehicles \n");
    printf("6. Add random vehicle\n");
    printf("7. Search vehicle \n");
    printf("0. Quit \n");
    printf("\nSelect option: ");
}

void execute_option(int option_num)
{
    if (!registry_check()) {
        fancy_print("ERROR", RED);
        printf("Registry could not be created.\n");
        return;
    }

    switch (option_num) {
        case 1:
            if (add_vehicle()) {
                fancy_print("SUCCESS", GREEN);
                printf("Vehicle was added.\n");
            }
            break;
        case 2:
            if (remove_vehicle()) {
                fancy_print("SUCCESS", GREEN);
                printf("Vehicle was removed.\n");
            }
            break;
        case 3:
            if (sort_registry()) {
                fancy_print("SUCCESS", GREEN);
                printf("Registry was sorted.\n");
            }
            break;
        case 4:
            show_info_one_vehicle();
            break;
        case 5:
            show_all();
            break;
        case 6:
            if (add_random_vehicle()) {
                fancy_print("SUCCESS", GREEN);
                printf("Following random generated car was added:\n");
                print_registry(count_lines() - 1, 1);
            }
            break;
        case 7:
            search_for_owner();
            break;
        default:
            fancy_print("ERROR", RED);
            printf("Option %d is not valid.\n", option_num);
            break;
    }
}

int main()
{
    char *input;
    int option;

    if (!registry_check()) {
        fancy_print("ERROR", RED);
        printf("Registry could not be created.\n");
        return 0;
    }

    // For seeding the random generator once
    srand(time(NULL));

    do {
        registry_check();
        print_options();
        input = read_string();

        if (input[0] >= 48 && input[0] <= 55) {
            option = atoi(input);
            if (option != 0)
                execute_option(option);
        } else {
            fancy_print("ERROR", RED);
            printf("Option \"%s\" is not valid.\n", input);
            option = -1; // Because string results to 0
        }
    } while (option != 0);

    return 1;
}