#include <stdio.h>

int main()
{
    int input[10];
    int i = 0;
    
    while (i < 10) {
        scanf("%d", &input[i]);
        i++;
    }
    
    int largest, smallest = input[0];
    i = 1;

    while (i <= 10) {
        if (input[i - 1] < smallest)
            smallest = input[i - 1];
        else if (input[i - 1] > largest)
            largest = input[i - 1];
        i++;
    }
    
    printf("%d %d\n", largest, smallest);
    return 0;
}