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
#define YELLOW 14

// The general limit for input is 31 chars (the last char is the null terminator)
#define INPUT_LIMIT 32
#define TYPE_LIMIT 12
#define BRAND_LIMIT 12
#define LICENSE_PLATE_LIMIT 7
#define OWNER_NAME_LIMIT 20
#define OWNER_AGE_LIMIT 100

// For the table view printing
#define PADDING 3
#define INDEX_WIDTH 8
#define AGE_WIDTH 3

typedef struct {
    char *name;
    int age;
} person;

typedef struct {
    char *type;
    char *brand;
    char *license_plate;
    person owner;
} vehicle;

// utils.c
void fancy_print(char *text, int color);
void free_vehicle(vehicle *v);
void free_vehicles(vehicle *vehicles);
vehicle *get_vehicles();
int is_valid(void *input, int type);
char *trim(char *str);
void print_divider();
int is_registry_valid();
int count_fields(char *line);
vehicle get_data_from_line(char *line);
int get_random_number(int min, int max);
char *get_random_license_plate();
int is_license_plate_unique(char *license_plate);

// file.c
int registry_check();
int write_to_registry(char *path, vehicle v);
int count_lines();
char *get_line(int line_index);
int print_registry(int start, int print_count);
int delete_line(int line_index);
char *read_string();
int read_int();

// functions.c
int add_vehicle ();
int remove_vehicle ();
int sort_registry();
void show_info_one_vehicle ();
int show_all();
int add_random_vehicle();
int search_for_owner();

#endif