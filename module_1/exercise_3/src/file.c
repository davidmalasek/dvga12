// Author: David Malášek

#include "../include/file.h"

int is_registry_available()
{
    FILE *file = fopen("./data/registry.csv", "r");
    if (!file) {
        fancy_print("There was an error while opening the registry.", RED);
        return 0;
    }
    fclose(file);
    return 1;
}

int write_to_registry(char *path, struct vehicle v)
{
    FILE *file = fopen(path, "a");
    if (!file) {
        fancy_print("There was an error while opening the registry.", RED);
        return 0;
    }

    fprintf(file, "%s,%s,%s,%s,%d\n", v.type, v.brand, v.license_plate, v.owner.name, v.owner.age);
    fclose(file);
    return 1;
}

int count_lines()
{
    FILE *file = fopen("./data/registry.csv", "r");
    if (!file) {
        fancy_print("There was an error while opening the registry.", RED);
        return -1;
    }

    int count = 0;
    int current_char;

    while ((current_char = fgetc(file)) != EOF) {
        if (current_char == '\n')
            count++;
    }

    fclose(file);
    return count;
}

/**
 * Extracts vehicle data from a line (string) from csv file.
 * Returned value must be freed.
 */
struct vehicle get_data_from_line(char *line)
{
    struct vehicle vehicle;
    
    // Remove newline
    line[strcspn(line, "\n")] = '\0';

    vehicle.type = strdup(strtok(line, ","));
    vehicle.brand = strdup(strtok(NULL, ","));
    vehicle.license_plate = strdup(strtok(NULL, ","));
    vehicle.owner.name = strdup(strtok(NULL, ","));
    vehicle.owner.age = atoi(strtok(NULL, ","));

    return (vehicle);
}

/**
 * Returns a line (string) from registry.
 * Returned value must be freed.
 */
char *get_line(int line_index)
{
    FILE *file = fopen("./data/registry.csv", "r");
    if (!file) {
        fancy_print("There was an error while opening the registry.", RED);
        return 0;
    }

    int current_line = 0;
    char line[155];

    while (fgets(line, sizeof(line), file)) {

        if (current_line == line_index) {
            fclose(file);

            char *result = malloc(strlen(line) + 1);
            if (!result)
                return NULL;
            result = strcpy(result, line);

            return result;
        }
        current_line++;
    }
    fclose(file);
    return NULL;
}

/*
start - on which line to start printing (indexed from 0)
print_count - how many lines to print
*/
int print_registry(int start, int print_count)
{
    FILE *file = fopen("./data/registry.csv", "r");
    if (!file) {
        fancy_print("There was an error while opening the registry.", RED);
        return 0;
    }

    int current_line = 0;
    int printed_lines = 0;
    char line[155];

    struct vehicle v;

    printf("\n%-12s %-12s %-12s %-12s %-20s %s\n", "Index", "Type", "Brand", "Plate", "Name", "Age");
    printf("----------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {

        if (current_line >= start && printed_lines < print_count) {
            v = get_data_from_line(line);

            printf("%-12d %-12s %-12s %-12s %-20s %3d\n", current_line + 1, v.type, v.brand, v.license_plate, v.owner.name, v.owner.age);
            printed_lines++;
        }
        current_line++;
    }
    fclose(file);
    return 1;
}

int delete_line(int line_index)
{
    FILE *in = fopen("./data/registry.csv", "r");
    FILE *out = fopen("./data/temp.csv", "w");

    if (!in) {
        fancy_print("Error opening registry.csv", RED);
        return 0;
    }

    if (!out) {
        fancy_print("Error creating temp.csv", RED);
        fclose(in);
        return 0;
    }

    char buffer[155];
    int current_line = 0;

    while (fgets(buffer, sizeof(buffer), in)) {
        if (current_line != line_index) {
            fputs(buffer, out);
        }
        current_line++;
    }

    fclose(in);
    fclose(out);

    remove("./data/registry.csv");
    rename("./data/temp.csv", "./data/registry.csv");

    return 1;
}

char *read_string()
{
    char buffer[32];

    // Read from stdin and return NULL if there was an error
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return NULL;

    // Remove newline
    buffer[strcspn(buffer, "\n")] = '\0';

    char *result = malloc(strlen(buffer) + 1);
    if (!result)
        return NULL;
    
    strcpy(result, buffer);
    
    return (result);
}

int read_int()
{
    char buffer[32];

    fgets(buffer, 31, stdin);
    return (atoi(buffer));
}