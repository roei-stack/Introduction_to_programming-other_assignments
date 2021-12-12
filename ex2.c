#include <stdio.h>

int kbonachi(int n, int k)
{
    if (n <= k)
        return 1;
    if (n == k + 1)
        return k;
    return 2 * kbonachi(n - 1, k) - kbonachi(n - k - 1, k);
}

int main()
{
    printf("%d", kbonachi(7, 3));

    return 0;
}
