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

int write_to_registry(struct vehicle v, struct person o)
{
    FILE *file = fopen("./data/registry.csv", "a");
    if (!file) {
        fancy_print("There was an error while opening the registry.", RED);
        return 0;
    }

    fprintf(file, "%s,%s,%s,%s,%d\n", v.type, v.brand, v.license_plate, o.name, o.age);
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

// void delete_line(int index)
// {

// }

/*
start - on which line to start printing (indexed from 0)
print_count - how many lines to print
*/
int read_csv(int start, int print_count)
{
    FILE *file = fopen("./data/registry.csv", "r");
    if (!file) {
        fancy_print("There was an error while opening the registry.", RED);
        return 0;
    }

    int line_num = 0;
    int printed_lines = 0;
    char line[155];

    struct vehicle v;
    struct person p;

    printf("\n%-12s %-12s %-12s %-12s %-20s %s\n", "Index", "Type", "Brand", "Plate", "Name", "Age");
    printf("----------------------------------------------------------------------------\n");
    while (fgets(line, sizeof(line), file)) {

        if (line_num >= start && printed_lines < print_count) {
            // Remove newline
            line[strcspn(line, "\n")] = '\0';

            v.type = strtok(line, ",");
            v.brand  = strtok(NULL, ",");
            v.license_plate   = strtok(NULL, ",");
            p.name  = strtok(NULL, ",");
            p.age = atoi(strtok(NULL, ","));

            printf("%-12d %-12s %-12s %-12s %-20s %3d\n", line_num + 1, v.type, v.brand, v.license_plate, p.name, p.age);
            printed_lines++;
        }
        line_num++;
    }
    fclose(file);
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