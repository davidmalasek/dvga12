#include <stdio.h>
#include <math.h>

float sum(float *array, int size)
{
    int i = 0;
    float sum = 0;

    while (i < size) {
        sum += array[i];
        i++;
    }
    return (sum);
}

float average(float *array, int size)
{
    return (sum(array, size) / size);
}

float standard_deviation(float *array, int size)
{
    int i = 0;
    float current = 0, sum_of_square_deviations = 0;
    float avg = average(array, size);

    if (size == 1)
        return 0.0f;

    while (i < size) {
        current = array[i];
        sum_of_square_deviations += (current - avg) * (current - avg);
        i++;
    }

    return (sqrtf(sum_of_square_deviations / (size - 1)));
}

int create_array(float *array, int size)
{
    int i = 0;

    while (i < size) {
        scanf("%f", &array[i]);
        if (array[i] < 0 || array[i] > 1000)
            return 1;
        i++;
    }
    return 0;
}

int main()
{
    int size;

    scanf("%d", &size);

    if (size < 1 || size > 100)
        return 1;

    float array1[size];

    if (create_array(array1, size))
        return 1;

    printf("%.6f\n", standard_deviation(array1, size));
    return 0;
}