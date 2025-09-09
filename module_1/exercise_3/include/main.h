// Author: David Malášek

#include <stdio.h>

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