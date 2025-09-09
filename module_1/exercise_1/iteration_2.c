#include <stdio.h>

int main()
{
    int year;

    scanf("%d", &year);

    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
        printf("t\n");
        return 0;
    }
    printf("f\n");
    return 0;
}