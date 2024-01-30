#include <stdio.h>
#include <string.h>

int cnt = 0;

void arrangement(int n, char *arr, int i, char before, char result[][n])
{
    if (i == n)
    {
        arr[n] = '\0';
        for (int i = 0; i < n; i++)
        {
            result[cnt][i] = arr[i];
        }
        cnt++;
        return;
    }
    if (before != 'S')
    {
        arr[i] = 'S';
        arrangement(n, arr, i + 1, 'S', result);
    }
    else if (before != 'M')
    {
        arr[i] = 'M';
        arrangement(n, arr, i + 1, 'M', result);
    }
    else if (before != 'L')
    {
        arr[i] = 'L';
        arrangement(n, arr, i + 1, 'L', result);
    }
}

int main()
{
    int n;
    printf("Pedestals:  ");
    scanf("%d", &n);
    if (n >= 1 && n <= 8)
    {
        char arr[n];
        char result[500][n];
        arrangement(n, arr, 0, ' ', result);
        printf("Total possibilities: %d\n", cnt);
        printf("All possible arrangements:\n");
        for (int i = 0; i < cnt; i++)
        {
            for (int x = 0; x < n; x++)
            {
                printf("%c", result[i][x]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Error! n must be in the bound [1,8]");
    }

    return 0;
}