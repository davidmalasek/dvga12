#include <stdio.h>
#include <math.h>

void calc(float param1, float param2, char operator)
{
    float result;

    if ((operator == '/' || operator == '^') && param2 == 0) {
        printf("NaN\n");
        return;
    }

    if (operator == '+') {
        result = param1 + param2;
    } else if (operator == '-') {
        result = param1 - param2;
    } else if (operator == '*') {
        result = param1 * param2;
    } else if (operator == '/') {
        result = param1 / param2;
    } else if (operator == '^') {
        result = pow(param1, param2);
    }

    printf("%g\n", result);
}

int main()
{
    float param1, param2;
    char operator;

    scanf("%f %c %f", &param1, &operator, &param2);

    calc(param1, param2, operator);
    return 0;
}