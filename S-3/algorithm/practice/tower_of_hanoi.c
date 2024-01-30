#include <stdio.h>

void toh(int n, char A, char B, char C)
{
    if (n >= 1)
    {
        // printf("Move last disc from %c to %c\n", A, C);
        toh(n - 1, A, C, B);
        printf("Move a disc from %c to %c\n", A, C);
        toh(n - 1, B, A, C);
        return;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    toh(3, 'A', 'C', 'B');
}