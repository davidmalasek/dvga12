// Author: David Malášek

#include "../include/file.h"

/**
 * Prints string in red color, with new line at the beginning and ending.
 */
void fancy_print(char *text, int color)
{
    if (color == 11)
        printf("\n\033[1;31m%s\033[0m\n", text);
    else if (color == 12)
        printf("\n\033[1;32m%s\033[0m\n", text);
    else if (color == 13)
        printf("\n\033[1;34m%s\033[0m\n", text);
    else
        printf("\n%s\n", text);
}

void add_vehicle ()
{
    struct vehicle vehicle;
    struct person owner;

    if (!is_registry_available())
        return;

    if (count_lines() == 10) {
        fancy_print("Cannot add vehicle. The registry is full.", RED);
        return;
    }

    printf("\nType: ");
    vehicle.type = read_string();

    printf("Brand: ");
    vehicle.brand = read_string();

    printf("License plate: ");
    vehicle.license_plate = read_string();

    printf("Owner name: ");
    vehicle.owner.name = read_string();

    printf("Owner age: ");
    vehicle.owner.age = read_int();

    if (!write_to_registry(vehicle))
        return;

    fancy_print("✅ The vehicle was added.", 0);
    
    free(vehicle.type);
    free(vehicle.brand);
    free(vehicle.license_plate);
    free(vehicle.owner.name);
}

void add_random_vehicle() 
{
    char *types[] = {"SUV", "Cabrio", "Hatchback", "Sedan", "Pickup"};
    char *brands[] = {"Skoda", "BMW", "Audi", "Mercedes", "Tesla"};
    char *licence_plates[] = {"ABC1234", "1BVX999", "CZ2025XY", "TOY2023A", "SKODA88X"};
    char *names[] = {"John Doe", "Elon Musk", "Tom Cruise", "Brad Pitt", "Michael Jackson"};
    int ages[] = {21, 30, 50, 33, 67};

    struct vehicle v;
    struct person p;

    // For seeding the random generator once
    srand((unsigned) time(NULL));

    v.type = types[rand() % 5];
    v.brand = brands[rand() % 5];
    v.license_plate = licence_plates[rand() % 5];
    v.owner.name = names[rand() % 5];
    v.owner.age = ages[rand() % 5];
    
    if (!write_to_registry(v))
        return;

    fancy_print("✅ Following random generated car was added:", 0);
    print_registry(count_lines() - 1, 1);
}

void remove_vehicle ()
{
    int vehicle_index;
    int vehicle_count = count_lines();

    printf("\nEnter vehicle index (1-%d): ", vehicle_count);
    vehicle_index = read_int();

    if (vehicle_index < 1 || vehicle_index > vehicle_count) {
        fancy_print("Invalid index", RED);
        return;
    }

    delete_line(vehicle_index - 1);

    fancy_print("✅ Vehicle was succesfully removed.", 0);
}

void sort_registry()
{
    int vehicle_count = count_lines();
    struct vehicle vehicles[vehicle_count];
    int i, e;

    i = 0;

    while (i < vehicle_count) {
        vehicles[i] = get_data_from_line(get_line(i));
        i++;
    }

    i = 0;
    e = 0;

    while (i < vehicle_count - 1) {
        e = 0;
        while (e < vehicle_count - i - 1) {
            if (strcmp(vehicles[e].owner.name, vehicles[e + 1].owner.name) > 0) {
                struct vehicle temp = vehicles[e];
                vehicles[e] = vehicles[e + 1];
                vehicles[e + 1] = temp;
            }
            e++;
        }
        i++;
    }

    // I ended here
}

void show_info_one_vehicle () {
    int vehicle_index;

    printf("\nEnter vehicle index (1-%d): ", count_lines());
    vehicle_index = read_int();

    if (vehicle_index > count_lines() || vehicle_index < 1) {
        fancy_print("Invalid index", RED);
        return;
    }
    print_registry(vehicle_index - 1, 1);
}