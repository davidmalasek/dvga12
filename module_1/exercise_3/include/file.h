// Author: David Malášek

#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int read_int();
char *read_string();
void write_to_registry(struct vehicle vehicle, struct person owner);
int count_lines();
void read_csv(int start, int print_count);

// functions.c
void add_vehicle ();
void remove_vehicle ();
void show_info_one_vehicle ();

#endif