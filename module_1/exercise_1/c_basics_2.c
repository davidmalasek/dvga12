#include <stdio.h>

int main()
{
    char input;

    scanf("%c", &input);

    if (input < 98 || input > 121)
        return 1;

    char before = input - 1;
    char after = input + 1;

    printf("%c %c\n", before, after);
    return 0;
}