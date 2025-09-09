#include <stdio.h>

int main()
{
    char input;
    char *hej;

    scanf("%c", &input);

    switch (input)
    {
        case 's':
            printf("hej\n");
            break;
        case 'S':
            printf("hej\n");
            break;
        case 'e':
            printf("hello\n");
            break;
        case 'E':
            printf("hello\n");
            break;
        case 'g':
            printf("hallo\n");
            break;
        case 'G':
            printf("hallo\n");
            break;
    }
    return 0;
}