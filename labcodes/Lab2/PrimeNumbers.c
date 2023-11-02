#include <stdio.h>
#include <stdbool.h>
#include <omp.h>
bool isPrime(int num)
{
    if (num <= 1)
        return false;
    if (num <= 3)
        return true;
    if (num % 2 == 0 || num % 3 == 0)
        return false;
    for (int i = 5; i * i <= num; i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}
void findPrimesParallel(int n)
{
#pragma omp parallel for 
    for (int i = 1; i <= n; i++)
    {
        if (isPrime(i))
        {
#pragma omp critical
            printf("%d ", i);
        }
    }
}
int main()
{
    int n = 100; // Set the range upper bound
    printf("NIVED KRISHNA\n");
    printf("2021BCS0028\n");
    printf("Prime numbers from 1 to %d:\n", n);
    findPrimesParallel(n);
    printf("\n");
    return 0;
}