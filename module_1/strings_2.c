#include <stdio.h>

int main()
{
    char enc_message[100];

    scanf("%99s", enc_message);

    char *character = enc_message;

    while (*character) {
        printf("%c", *character - 3);
        character++;
    }
    printf("\n");
    return 0;
}