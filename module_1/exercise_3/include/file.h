// Author: David Malášek

#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RED 1
#define GREEN 2
#define BLUE 2

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
int write_to_registry(struct vehicle vehicle, struct person owner);
int count_lines();
int read_csv(int start, int print_count);

// functions.c
void fancy_print(char *text, int color);
void add_vehicle ();
void remove_vehicle ();
void show_info_one_vehicle ();
void add_random_vehicle();

#endif