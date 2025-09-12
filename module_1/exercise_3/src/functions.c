// Author: David Malášek

#include "../include/file.h"

void add_vehicle ()
{
    struct vehicle vehicle;
    struct person owner;

    printf("\nType: ");
    vehicle.type = read_string();

    printf("Brand: ");
    vehicle.brand = read_string();

    printf("License plate: ");
    vehicle.license_plate = read_string();

    printf("Owner name: ");
    owner.name = read_string();

    printf("Owner age: ");
    owner.age = read_int();

    write_to_registry(vehicle, owner);
    
    free(vehicle.type);
    free(vehicle.brand);
    free(vehicle.license_plate);
    free(owner.name);
}

void remove_vehicle ()
{

}

void show_info_one_vehicle () {
    int vehicle_index;

    printf("\nEnter vehicle index: ");
    vehicle_index = read_int();

    if (vehicle_index > count_lines() || vehicle_index < 1) {
        printf("\033[1;31mInvalid index: %d\033[0m\n", vehicle_index);
        return;
    }
    read_csv(vehicle_index - 1, 1);
}