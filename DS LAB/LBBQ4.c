#include <stdio.h>

int main()
{
    int a[5] = {9, 5, 1, 4, 3};
    int i, j, key;

    for(i = 1; i < 5; i++)
    {
        key = a[i];
        j = i - 1;

        while(j >= 0 && a[j] > key)
        {
            a[j+1] = a[j];
            j--;
        }

        a[j+1] = key;

        printf("Pass %d: ", i);
        for(j = 0; j < 5; j++)
            printf("%d ", a[j]);

        printf("\n");
    }

    return 0;
}