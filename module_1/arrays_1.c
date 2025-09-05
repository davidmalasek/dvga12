#include <stdio.h>

void create_array(int *array, int size) {
    int i = 0;

    while (i < size) {
        scanf("%d", &array[i]);
        i++;
    }
}

int main()
{
    int size;

    scanf("%d", &size);

    int array1[size];
    int array2[size];

    create_array(array1, size);
    create_array(array2, size);
    
    int i = 0;

    while (i < size) {
        printf("%d\n", array1[i] + array2[i]);
        i++;
    }
    return 0;
}