#include <stdio.h>

int main()
{
    int first_num;
    int second_num;

    scanf("%d %d", &first_num, &second_num);

    int sum = first_num + second_num;
    int product = first_num * second_num;
    int quotient = first_num / second_num;

    printf("%d %d %d\n", sum, product, quotient);
    return 0;
}