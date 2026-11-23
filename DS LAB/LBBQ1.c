#include <stdio.h>

int main()
{
    int a[100], mark[101] = {0};
    int n, i, max;

    printf("Enter size: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    max = a[0];

    for(i = 0; i < n; i++)
    {
        if(a[i] > max)
            max = a[i];

        mark[a[i]] = 1;
    }

    printf("Missing numbers: ");
    for(i = 1; i <= max; i++)
    {
        if(mark[i] == 0)
            printf("%d ", i);
    }

    return 0;
}