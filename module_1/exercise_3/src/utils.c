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
    else if (color == YELLOW)
        printf("\n\033[1;33m%s\033[0m\n", text);
    else
        printf("\n%s\n", text);
}

void free_vehicle(vehicle *v)
{
    free(v->type);
    free(v->brand);
    free(v->license_plate);
    free(v->owner.name);
}

/**
 * Frees items of an array of vehicles including the array itself.
 */
void free_vehicles(vehicle *vehicles)
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
vehicle *get_vehicles()
{
    int vehicle_count = count_lines();
    vehicle *vehicles = malloc(vehicle_count * sizeof(vehicle));

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

int is_valid(void *input, int type)
{
    if (!input)
        return 0;
        
    char *str = (char *)input;

    if (strlen(str) == 0)
        return 0;

    if (type == TYPE) { // Only A-Z and a-z
        int i = 0;
        while (str[i] != '\0') {
            if (!isalpha((unsigned char)str[i])) {
                return 0;
            }   
        i++;
        }
    } else if (type == BRAND) { // Only A-Z, a-z, spaces and dashes
        int i = 0;
        while (str[i] != '\0') {
            if (!(isalpha((unsigned char)str[i]) || str[i] == '-' || str[i] == ' ')) {
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
        if (*(int *)input < 0 || *(int *)input > OWNER_AGE_LIMIT) {
            return 0;
        }
    }

    return 1;
}

char *trim(char *str)
{
    char *end;

    while (isspace((unsigned char)*str))
        str++;

    if (*str == '\0')
        return str;

    end = str + strlen(str) - 1;
    
    while (end > str && isspace((unsigned char)*end))
        end--;

    *(end + 1) = '\0';

    return str;
}

void print_divider()
{
    int i = 0;
    int total_width = INDEX_WIDTH
                    + (TYPE_LIMIT + PADDING)
                    + (BRAND_LIMIT + PADDING)
                    + (LICENSE_PLATE_LIMIT + PADDING)
                    + (OWNER_NAME_LIMIT + PADDING)
                    + AGE_WIDTH
                    + 5; // space between columns

    while (i < total_width) {
        putchar('-');
        i++;
    }
    putchar('\n');
}

int is_registry_valid()
{
    int i = 0;
    vehicle current_vehicle;
    char *current_line;

    if (count_lines() > 10)
        return 0;

    while (i < count_lines()) {
        current_line = get_line(i);
        if (!current_line || count_fields(current_line) != 5)
            return 0;
        
        current_vehicle = get_data_from_line(current_line);
        
        if (!is_valid(current_vehicle.type, TYPE) ||
        !is_valid(current_vehicle.brand, BRAND) ||
        !is_valid(current_vehicle.license_plate, LICENSE_PLATE) ||
        !is_valid(current_vehicle.owner.name, OWNER_NAME) ||
        !is_valid(&current_vehicle.owner.age, OWNER_AGE))
        {
            free(current_line);
            free_vehicle(&current_vehicle);
            return 0;
        }
        i++;
    }
    free(current_line);
    free_vehicle(&current_vehicle);
    return 1;
}

/**
 * Returns number of fields in a line.
 */
int count_fields(char *line)
{
    int number_of_fields = 1;
    
    while(*line) {
        if (*line == ',')
            number_of_fields++;
        line++;
    }
    return number_of_fields;
}

/**
 * Extracts vehicle data from a line (string) from csv file.
 * Returned value must be freed.
 */
vehicle get_data_from_line(char *line)
{
    vehicle vehicle;
    char *token;
    
    // Remove newline
    line[strcspn(line, "\n")] = '\0';

    token = strtok(line, ",");
    vehicle.type = token ? strdup(token) : NULL;

    token = strtok(NULL, ",");
    vehicle.brand = token ? strdup(token) : NULL;

    token = strtok(NULL, ",");
    vehicle.license_plate = token ? strdup(token) : NULL;

    token = strtok(NULL, ",");
    vehicle.owner.name = token ? strdup(token) : NULL;

    token = strtok(NULL, ",");
    vehicle.owner.age = token ? atoi(token) : -1;

    return (vehicle);
}

int get_random_number(int min, int max)
{
    int random_number = min + rand() % (max - min + 1);

    return random_number;
}

/**
 * Generates a random license plate. Returned string must be freed.
 */
char *get_random_license_plate()
{
    char *random_license_plate = malloc(LICENSE_PLATE_LIMIT + 1);
    if (!random_license_plate)
        return NULL;

    random_license_plate[0] = (char)get_random_number(65, 90); // A-Z
    random_license_plate[1] = (char)get_random_number(65, 90); // A-Z
    random_license_plate[2] = (char)get_random_number(65, 90); // A-Z
    random_license_plate[3] = (char)get_random_number(48, 57); // 0-9
    random_license_plate[4] = (char)get_random_number(48, 57); // 0-9
    random_license_plate[5] = (char)get_random_number(48, 57); // 0-9
    random_license_plate[6] = (char)get_random_number(48, 57); // 0-9
    random_license_plate[7] = '\0';

    return random_license_plate;
}

int is_license_plate_unique(char *license_plate)
{
    vehicle *vehicles = get_vehicles();

    if (!vehicles)
        return -1;

    int i = 0; 

    while (i < count_lines()) {
        if (strcmp(vehicles[i].license_plate, license_plate) == 0)
            return 0;
        i++;
    }
    free_vehicles(vehicles);
    return 1;
}