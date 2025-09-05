#include <stdio.h>

int main()
{
    char buffer[100];

    printf("");
    fgets(buffer, 100, stdin);

    int i = 1;
    int ab_counter = 0;

    while (i <= 100) {
        if (buffer[i - 1] == 'a' && buffer[i] == 'b')
            ab_counter++;
        i++;
    }
    printf("%d\n", ab_counter);
    return 0;
}