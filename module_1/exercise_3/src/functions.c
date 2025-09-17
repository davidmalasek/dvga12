// Author: David Malášek

#include "../include/file.h"

int add_vehicle ()
{
    struct vehicle vehicle;

    if (!is_registry_available())
        return 0;

    if (count_lines() == 10) {
        fancy_print("Cannot add vehicle. The registry is full.", RED);
        return 0;
    }

    printf("\nType: ");
    vehicle.type = read_string();

    if (!validate(vehicle.type, TYPE)) {
        fancy_print("Invalid vehicle type. Use only alphabet letters, spaces and dashes.", RED);
        return 0;
    }

    printf("Brand: ");
    vehicle.brand = read_string();

    if (!validate(vehicle.brand, BRAND)) {
        fancy_print("Invalid vehicle brand. Use only alphabet letters, spaces and dashes.", RED);
        return 0;
    }

    printf("License plate: ");
    vehicle.license_plate = read_string();

    if (!validate(vehicle.license_plate, LICENSE_PLATE)) {
        fancy_print("Invalid license plate. Use only uppercase letters and numbers.", RED);
        return 0;
    }

    printf("Owner name: ");
    vehicle.owner.name = read_string();

    if (!validate(vehicle.owner.name, OWNER_NAME)) {
        fancy_print("Invalid owner name. Use only alphabet letters and spaces.", RED);
        return 0;
    }

    printf("Owner age: ");
    vehicle.owner.age = read_int();

    if (!validate(&vehicle.owner.age, OWNER_AGE)) {
        fancy_print("Invalid owner age. Enter a positive number.", RED);
        return 0;
    }

    if (!write_to_registry("./data/registry.csv", vehicle))
        return 0;
    
    free(vehicle.type);
    free(vehicle.brand);
    free(vehicle.license_plate);
    free(vehicle.owner.name);

    return 1;
}

int remove_vehicle ()
{
    int vehicle_index;
    int vehicle_count = count_lines();

    printf("\nEnter vehicle index (1-%d): ", vehicle_count);
    vehicle_index = read_int();

    if (vehicle_index < 1 || vehicle_index > vehicle_count) {
        fancy_print("Invalid index", RED);
        return 0;
    }

    delete_line(vehicle_index - 1);
    return 1;
}

int sort_registry()
{
    int vehicle_count = count_lines();
    struct vehicle *vehicles = get_vehicles();

    if (!vehicles || vehicle_count == 0) {
        fancy_print("Registry is empty or could not be loaded.", RED);
        return 0;
    }

    int i = 0;
    int e = 0;

    // Bubble sort for sorting
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

    // Create temporary file
    FILE *temp = fopen("./data/temp.csv", "w");
    if (!temp) {
        free_vehicles(vehicles);
        fancy_print("There was an error while working with the registry.", RED);
        return 0;
    }
    fclose(temp);

    i = 0;

    while (i < vehicle_count) {
        write_to_registry("./data/temp.csv", vehicles[i]);
        i++;
    }

    remove("./data/registry.csv");
    rename("./data/temp.csv", "./data/registry.csv");

    free_vehicles(vehicles);
    return 1;
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

int add_random_vehicle() 
{
    char *types[] = {"SUV", "Cabrio", "Hatchback", "Sedan", "Pickup"};
    char *brands[] = {"Skoda", "BMW", "Audi", "Mercedes", "Tesla"};
    char *licence_plates[] = {"ABC1234", "1BVX999", "CZ2025XY", "TOY2023A", "SKODA88X"};
    char *names[] = {"John Doe", "Elon Musk", "Tom Cruise", "Brad Pitt", "Michael Jackson"};
    int ages[] = {21, 30, 50, 33, 67};

    struct vehicle v;

    // For seeding the random generator once
    srand((unsigned) time(NULL));

    v.type = types[rand() % 5];
    v.brand = brands[rand() % 5];
    v.license_plate = licence_plates[rand() % 5];
    v.owner.name = names[rand() % 5];
    v.owner.age = ages[rand() % 5];
    
    if (!write_to_registry("./data/registry.csv", v))
        return 0;

    return 1;
}

int search_for_owner()
{
    char *query;
    
    printf("\nEnter owner name: ");
    query = read_string();

    if (!validate(query, OWNER_NAME)) {
        fancy_print("Invalid owner name. Use only alphabet letters and spaces..", RED);
        return 0;
    }
    
    sort_registry();
    struct vehicle *vehicles = get_vehicles();

    int left = 0;
    int right = count_lines() - 1;
    int mid;

    while (left <= right) {
        mid = left + (right - left) / 2;

        if (strstr(vehicles[mid].owner.name, query) != NULL) {
            print_registry(mid, 1);
            free_vehicles(vehicles);
            return 1;
        }
        
        if (strcmp(vehicles[mid].owner.name, query) < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    free_vehicles(vehicles);
    return 0;
}