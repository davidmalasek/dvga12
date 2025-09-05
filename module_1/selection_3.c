#include <stdio.h>

void get_sum_and_number(int n, int result[2]) {
    int sum = 1;
    int addition = 1;

    while (sum <= n) {
        addition++;
        sum += addition;
    }
    result[0] = sum;
    result[1] = addition;
}

int main()
{
    int input;
    int sum_and_number[2];

    scanf("%d", &input);

    get_sum_and_number(input, sum_and_number);
    printf("%d %d\n", sum_and_number[0], sum_and_number[1]);
    return 0;
}