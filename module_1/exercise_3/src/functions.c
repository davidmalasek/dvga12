// Author: David Malášek

#include "../include/file.h"

int add_vehicle ()
{
    vehicle vehicle;

    if (count_lines() == 10) {
        fancy_print("WARNING", YELLOW);
        printf("Cannot add vehicle, the registry is full.\n");
        return 0;
    }

    printf("\nType: ");
    vehicle.type = read_string();

    if (!vehicle.type) {
        fancy_print("ERROR", RED);
        printf("Could not read the vehicle type.\n");
        return 0;
    }

    if (strlen(vehicle.type) > TYPE_LIMIT) {
        fancy_print("ERROR", RED);
        printf("Entered vehicle type exceeded length of %d characters.\n", TYPE_LIMIT);
        return 0;
    } else if (!is_valid(vehicle.type, TYPE)) {
        fancy_print("ERROR", RED);
        printf("Invalid vehicle type. Use only alphabet letters.\n");
        return 0;
    }

    printf("Brand: ");
    vehicle.brand = read_string();

    if (!vehicle.brand) {
        fancy_print("ERROR", RED);
        printf("Could not read the vehicle brand.\n");
        return 0;
    }

    if (strlen(vehicle.brand) > BRAND_LIMIT) {
        fancy_print("ERROR", RED);
        printf("Entered vehicle brand exceeded length of %d characters.\n", BRAND_LIMIT);
        return 0;
    } else if (!is_valid(vehicle.brand, BRAND)) {
        fancy_print("ERROR", RED);
        printf("Invalid vehicle brand. Use only alphabet letters, spaces and dashes.\n");
        return 0;
    }

    printf("License plate: ");
    vehicle.license_plate = read_string();

    if (!vehicle.license_plate) {
        fancy_print("ERROR", RED);
        printf("Could not read the vehicle license plate.\n");
        return 0;
    }

    if (strlen(vehicle.license_plate) > LICENSE_PLATE_LIMIT) {
        fancy_print("ERROR", RED);
        printf("Entered license plate exceeded length of %d characters.\n", LICENSE_PLATE_LIMIT);
        return 0;
    } else if (!is_valid(vehicle.license_plate, LICENSE_PLATE)) {
        fancy_print("ERROR", RED);
        printf("Invalid license plate. Use only uppercase letters and numbers.\n");
        return 0;
    }

    printf("Owner name: ");
    vehicle.owner.name = read_string();

    if (!vehicle.owner.name) {
        fancy_print("ERROR", RED);
        printf("Could not read the owner name.\n");
        return 0;
    }

    if (strlen(vehicle.owner.name) > OWNER_NAME_LIMIT) {
        fancy_print("ERROR", RED);
        printf("Entered owner name exceeded length of %d characters.\n", OWNER_NAME_LIMIT);
        return 0;
    } else if (!is_valid(vehicle.owner.name, OWNER_NAME)) {
        fancy_print("ERROR", RED);
        printf("Invalid owner name. Use only alphabet letters and spaces.\n");
        return 0;
    }

    printf("Owner age: ");
    vehicle.owner.age = read_int();

    if (!vehicle.owner.age) {
        fancy_print("ERROR", RED);
        printf("Could not read the owner age.\n");
        return 0;
    }

    if (!is_valid(&vehicle.owner.age, OWNER_AGE)) {
        fancy_print("ERROR", RED);
        printf("Invalid owner age. Enter a number from 0 to %d.\n", OWNER_AGE_LIMIT);
        return 0;
    }

    if (!write_to_registry("./data/registry.csv", vehicle)) {
        fancy_print("ERROR", RED);
        printf("Could not write to registry.\n");
        return 0;
    }

    free(vehicle.type);
    free(vehicle.brand);
    free(vehicle.license_plate);
    free(vehicle.owner.name);

    return 1;
}

int remove_vehicle ()
{
    int vehicle_count = count_lines();
    
    if (vehicle_count == 0) {
        fancy_print("WARNING", YELLOW);
        printf("The registry is empty.\n");
        return 0;
    }
    
    int vehicle_index;

    printf("\nEnter vehicle index (1-%d): ", vehicle_count);
    vehicle_index = read_int();

    if (vehicle_index < 1 || vehicle_index > vehicle_count) {
        fancy_print("ERROR", RED);
        printf("Index %d is not valid.\n", vehicle_index);
        return 0;
    }

    if (!delete_line(vehicle_index - 1)) {
        fancy_print("ERROR", RED);
        printf("Vehicle with index %d could not be removed.\n", vehicle_index);
        return 0;
    }

    return 1;
}

int sort_registry()
{
    int vehicle_count = count_lines();

    if (vehicle_count == 0) {
        fancy_print("WARNING", YELLOW);
        printf("The registry is empty.\n");
        return 0;
    } else if (vehicle_count == 1) {
        fancy_print("WARNING", YELLOW);
        printf("Only one vehicle in registry, no need to sort.\n");
        return 0;
    }

    vehicle *vehicles = get_vehicles();

    if (!vehicles || vehicle_count == 0) {
        fancy_print("ERROR", RED);
        printf("Registry is empty or could not be loaded.\n");
        return 0;
    }

    int i = 0;
    int e = 0;

    // Bubble sort for sorting
    while (i < vehicle_count - 1) {
        e = 0;
        while (e < vehicle_count - i - 1) {
            if (strcmp(vehicles[e].owner.name, vehicles[e + 1].owner.name) > 0) {
                vehicle temp = vehicles[e];
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
        fancy_print("ERROR", RED);
        printf("Could not create temporary registry.\n");
        return 0;
    }
    fclose(temp);
    
    i = 0;
    
    while (i < vehicle_count) {
        if (!write_to_registry("./data/temp.csv", vehicles[i])) {
            fancy_print("ERROR", RED);
            printf("Could not write to temporary registry.\n");
            remove("./data/registry.csv");
            free_vehicles(vehicles);
            return 0;
        }
        i++;
    }

    remove("./data/registry.csv");
    rename("./data/temp.csv", "./data/registry.csv");

    free_vehicles(vehicles);
    return 1;
}

void show_info_one_vehicle ()
{
    int vehicle_index;
    int vehicle_count = count_lines();

    if (vehicle_count == 0) {
        fancy_print("WARNING", YELLOW);
        printf("The registry is empty.\n");
        return;
    }

    if (vehicle_count == 1) {
        vehicle_index = 1;
    } else {
        printf("\nEnter vehicle index (1-%d): ", vehicle_count);
        vehicle_index = read_int();
    }

    if (vehicle_index > vehicle_count || vehicle_index < 1) {
        fancy_print("ERROR", RED);
        printf("Index %d is not valid.\n", vehicle_index);
        return;
    }
    if (!print_registry(vehicle_index - 1, 1)) {
        fancy_print("ERROR", RED);
        printf("Could not print info from the registry.\n");
        return;
    }
}

int show_all()
{
    if (count_lines() == 0) {
        fancy_print("WARNING", YELLOW);
        printf("The registry is empty.\n");
        return 0;
    }

    if (!is_registry_valid()) {
        fancy_print("ERROR", RED);
        printf("The registry is invalid.\n");
        return 0;
    }
    print_registry(0, count_lines());
    return 1;
}            

int add_random_vehicle() 
{
    if (count_lines() == 10) {
        fancy_print("WARNING", YELLOW);
        printf("Cannot add vehicle, the registry is full.\n");
        return 0;
    }

    char *types[] = {"SUV", "Cabrio", "Hatchback", "Sedan", "Pickup"};
    char *brands[] = {"Skoda", "BMW", "Audi", "Mercedes", "Tesla"};
    char *licence_plates[] = {"ABC1234", "1BVX999", "CZ2025XY", "TOY2023A", "SKODA88X"};
    char *names[] = {"John Doe", "Elon Musk", "Tom Cruise", "Brad Pitt", "Michael Jackson"};
    int ages[] = {21, 30, 50, 33, 67};

    vehicle v;

    // For seeding the random generator once
    srand((unsigned) time(NULL));

    v.type = types[rand() % 5];
    v.brand = brands[rand() % 5];
    v.license_plate = licence_plates[rand() % 5];
    v.owner.name = names[rand() % 5];
    v.owner.age = ages[rand() % 5];
    
    if (!write_to_registry("./data/registry.csv", v)) {
        fancy_print("ERROR", RED);
        printf("Could not write to registry.\n");
        return 0;
    }

    return 1;
}

int search_for_owner()
{
    if (count_lines() == 0) {
        fancy_print("WARNING", YELLOW);
        printf("The registry is empty.\n");
        return 0;
    }

    char *query;
    
    printf("\nEnter owner name (case-sensitive): ");
    query = read_string();

    if (!is_valid(query, OWNER_NAME)) {
        fancy_print("ERROR", RED);
        printf("Invalid owner name. Use only alphabet letters and spaces.\n");
        return 0;
    }
    
    sort_registry();
    vehicle *vehicles = get_vehicles();

    int left = 0;
    int right = count_lines() - 1;
    int mid;

    while (left <= right) {
        mid = left + (right - left) / 2;

        if (strstr(vehicles[mid].owner.name, query) != NULL) {
            free_vehicles(vehicles);
            if (!print_registry(mid, 1)) {
                fancy_print("ERROR", RED);
                printf("Could not print info from the registry.\n");
                return 0;
            }
            return 1;
        }
        
        if (strcmp(vehicles[mid].owner.name, query) < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    free_vehicles(vehicles);

    fancy_print("WARNING", YELLOW);
    printf("Could not find vehicle assigned to entered owner name.\n");
    return 0;
}