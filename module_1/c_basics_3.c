#include <stdio.h>

char *odd_or_even(int num)
{
    return (num % 2 == 0) ? "even" : "odd";
}

int main()
{
    int num1, num2, num3, num4, num5;

    scanf("%d\n%d\n%d\n%d\n%d", &num1, &num2, &num3, &num4, &num5);

    printf("%s\n%s\n%s\n%s\n%s\n", odd_or_even(num1), odd_or_even(num2), odd_or_even(num3), odd_or_even(num4), odd_or_even(num5));

    return 0;
}