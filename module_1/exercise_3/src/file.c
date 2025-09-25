// Author: David Malášek

#include "../include/file.h"

/**
 * Checks if registry exists, if not, creates one.
 */
int registry_check()
{
    FILE *file = fopen("./data/registry.csv", "r");
    if (file) {
        fclose(file);
        return 1;
    }

    // If registry does not exist
    file = fopen("./data/registry.csv", "w");
    if (!file)
        return 0;

    fclose(file);
    return 1;
}

int write_to_registry(char *path, vehicle v)
{
    FILE *file = fopen(path, "a");
    if (!file)
        return 0;

    fprintf(file, "%s,%s,%s,%s,%d\n", trim(v.type), trim(v.brand), trim(v.license_plate), trim(v.owner.name), v.owner.age);
    fclose(file);
    return 1;
}

/**
 * Returns actual number of lines (vehicles) in registry.
 * Returns -1 if there was a problem while opening the registry.
 */
int count_lines()
{
    FILE *file = fopen("./data/registry.csv", "r");
    if (!file)
        return -1;

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
 * Returns a line (string) from registry.
 * Returned value must be freed.
 */
char *get_line(int line_index)
{
    FILE *file = fopen("./data/registry.csv", "r");
    if (!file)
        return NULL;

    int current_line = 0;
    char line[(INPUT_LIMIT - 1) * 5 + 4 + 1 + 1];
    size_t len;

    while (fgets(line, sizeof(line), file)) {
        len = strlen(line);

        if (len > 0 && line[len - 1] != '\n' && !feof(file)) {
            fclose(file);
            return NULL;
        }

        if (current_line == line_index) {
            fclose(file);

            char *result = malloc(len + 1);
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
    if (!file)
        return 0;

    int current_line = 0;
    int printed_lines = 0;
    char line[(INPUT_LIMIT - 1) * 5 + 4 + 1 + 1];

    vehicle v;

    printf("\n%-*s %-*s %-*s %-*s %-*s %s\n", INDEX_WIDTH, "Index", TYPE_LIMIT + PADDING, "Type", BRAND_LIMIT + PADDING, "Brand", LICENSE_PLATE_LIMIT + PADDING, "Plate", OWNER_NAME_LIMIT + PADDING, "Name", "Age");
    print_divider();

    while (fgets(line, sizeof(line), file)) {

        if (current_line >= start && printed_lines < print_count) {
            v = get_data_from_line(line);

            printf("%-*d %-*s %-*s %-*s %-*s %3d\n", INDEX_WIDTH, current_line + 1, TYPE_LIMIT + PADDING, v.type, BRAND_LIMIT + PADDING, v.brand, LICENSE_PLATE_LIMIT + PADDING, v.license_plate, OWNER_NAME_LIMIT + PADDING, v.owner.name, v.owner.age);
            printed_lines++;
        }
        current_line++;
    }
    fclose(file);
    return 1;
}

/**
 * Deletes a line on specified index in the CSV file.
 */
int delete_line(int line_index)
{
    FILE *in = fopen("./data/registry.csv", "r");
    FILE *out = fopen("./data/temp.csv", "w");

    if (!in)
        return 0;

    if (!out) {
        fclose(in);
        return 0;
    }

    char buffer[(INPUT_LIMIT - 1) * 5 + 4 + 1 + 1];
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

/**
 * Returns a string from stdin, which needs to be freed after use.
 */
char *read_string()
{
    char buffer[INPUT_LIMIT];

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

/**
 * Returns an integer from stdin.
 */
int read_int()
{
    char buffer[INPUT_LIMIT];

    if (fgets(buffer, INPUT_LIMIT - 1, stdin) == NULL) 
        return -1; 
    return (atoi(buffer));
}