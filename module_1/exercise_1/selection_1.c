#include <stdio.h>

int main()
{
    float gross;

    scanf("%f", &gross);

    int threshold = 204000;
    float low = 0.3;
    float high = 0.5;
    float net;

    if (gross <= threshold)
        net = gross - (gross * low);
    else
        net = gross - (threshold * low + (gross - threshold) * high);

    printf("%.1f\n", net);
    return 0;
}