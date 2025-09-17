// Author: David Malášek

#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

// file.c
int is_registry_available();
int read_int();
char *read_string();
int write_to_registry(struct vehicle vehicle);
int count_lines();
int print_registry(int start, int print_count);
int delete_line(int line_index);
struct vehicle get_data_from_line(char *line);
char *get_line(int line_index);

// functions.c
void fancy_print(char *text, int color);
void add_vehicle ();
void remove_vehicle ();
void show_info_one_vehicle ();
void add_random_vehicle();
void sort_registry();

#endif