#include <stdio.h>

int main()
{
    int input, sum = 0;

    while (1) {
        scanf("%d", &input);
        if (input == 0)
            return 0;
        printf("%d\n", sum += input);
    }
    return 0;
}