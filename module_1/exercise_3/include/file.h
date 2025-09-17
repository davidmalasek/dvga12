// Author: David Malášek

#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define TYPE 1
#define BRAND 2
#define LICENSE_PLATE 3
#define OWNER_NAME 4
#define OWNER_AGE 5

// For fancy printing
#define RED 11
#define GREEN 12
#define BLUE 13

struct person {
    char *name;
    int age;
};
struct vehicle {
    char *type;
    char *brand;
    char *license_plate;
    struct person owner;
};

// utils.c
void fancy_print(char *text, int color);
void free_vehicle(struct vehicle *v);
void free_vehicles(struct vehicle *vehicles);
struct vehicle *get_vehicles();
int validate(void *input, int type);

// file.c
int is_registry_available();
int read_int();
char *read_string();
int write_to_registry(char *path, struct vehicle v);
int count_lines();
int print_registry(int start, int print_count);
int delete_line(int line_index);
struct vehicle get_data_from_line(char *line);
char *get_line(int line_index);

// functions.c
int add_vehicle ();
int remove_vehicle ();
int sort_registry();
void show_info_one_vehicle ();
int add_random_vehicle();
int search_for_owner();

#endif