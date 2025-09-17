// Author: David Malášek

#include "../include/file.h"

/**
 * Prints string in red color, with new line at the beginning and ending.
 */
void fancy_print(char *text, int color)
{
    if (color == RED)
        printf("\n\033[1;31m%s\033[0m\n", text);
    else if (color == GREEN)
        printf("\n\033[1;32m%s\033[0m\n", text);
    else if (color == BLUE)
        printf("\n\033[1;34m%s\033[0m\n", text);
    else
        printf("\n%s\n", text);
}

void free_vehicle(struct vehicle *v)
{
    free(v->type);
    free(v->brand);
    free(v->license_plate);
    free(v->owner.name);
}

/**
 * Frees items of an array of vehicles including the array itself.
 */
void free_vehicles(struct vehicle *vehicles)
{
    int i = 0;
    int count = count_lines(); // This function is only called when working with the whole registry

    if (!vehicles)
        return;

    while (i < count) {
        free_vehicle(&vehicles[i]);
        i++;
    }

    free(vehicles);
}

/**
 * Returns pointer to first item in an array of all vehicles in registry.
 */
struct vehicle *get_vehicles()
{
    int vehicle_count = count_lines();
    struct vehicle *vehicles = malloc(vehicle_count * sizeof(struct vehicle));

    if (!vehicles)
        return NULL;

    int i = 0;
    char *current_line;

    while (i < vehicle_count) {
        current_line = get_line(i);
        vehicles[i] = get_data_from_line(current_line);
        free(current_line);
        i++;
    }

    return vehicles;
}

int validate(void *input, int type)
{
    char *str = (char *)input;

    if (type == TYPE || type == BRAND) { // Only A-Z, a-z, spaces and dashes
        int i = 0;
        while (str[i] != '\0') {
            if (!isalpha((unsigned char)str[i]) && str[i] != ' ' && str[i] != '-') {
                return 0;
            }   
        i++;
        }
    } else if (type == LICENSE_PLATE) { // Only A-Z and 0-9
        int i = 0;
        while (str[i] != '\0') {
            if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))) {
                return 0;
            }
            i++;
        }
    } else if (type == OWNER_NAME) { // Only A-Z, a-z and spaces
        int i = 0;
        while (str[i] != '\0') {
            if (!isalpha((unsigned char)str[i]) && str[i] != ' ') {
                return 0;
            }   
        i++;
        }
    } else if (type == OWNER_AGE) { // Only positive integers
        if (*(int *)input <= 0 || *(int *)input > 120) {
            return 0;
        }
    }

    return 1;
}