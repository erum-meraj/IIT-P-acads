#include <stdio.h>
int cnt = 0;

void display(int arr[], int n)
{
    for (int i = 0; i < 2 * n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void arrangement(int arr[], int ele, int n)
{
    if (ele > n)
    {
        display(arr, n);
        cnt++;
        return;
    }
    else
    {
        for (int i = 0; i < 2 * n; i++)
        {
            if (arr[i] == 0 && (i + ele + 1) < 2 * n && arr[i + ele + 1] == 0)
            {
                arr[i] = ele;
                arr[i + ele + 1] = ele;
                arrangement(arr, ele + 1, n);
                arr[i] = 0;
                arr[i + ele + 1] = 0;
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter n:  ");
    scanf("%d", &n);
    if (n >= 1 && n <= 10)
    {
        int arr[2 * n];
        for (int i = 0; i < 2 * n; i++)
        {
            arr[i] = 0;
        }
        arrangement(arr, 1, n);
        if (cnt == 0)
        {
            printf("No possible solutions exist.\n");
        }
    }
    else
    {
        printf("N is out of the bound [1,10]\n");
    }

    return 0;
}