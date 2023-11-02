#include <stdio.h>
#include <omp.h>

#define N 100

int is_prime[N + 1];

void sieve()
{
    for (int i = 0; i <= N; i++)
    {
        is_prime[i] = 1;
    }

    is_prime[0] = is_prime[1] = 0;

    for (int p = 2; p * p <= N; p++)
    {
        if (is_prime[p] == 1)
        {
            for (int i = p * p; i <= N; i += p)
            {
                is_prime[i] = 0;
            }
        }
    }
}

int main()
{
    int count = 0;

    sieve();
    printf("NIVED KRISHNA\t 2021BCS0028\n");
#pragma omp parallel for reduction(+ : count)
    for (int i = 3; i < N; i += 2)
    {
        if (is_prime[i] && is_prime[i - 2])
        {
            count++;
            
            printf("%d and %d are consecutive prime numbers.\n", i - 2, i);
        }
    }

    printf("Total number of consecutive prime pairs less than 100: %d\n", count);

    return 0;
}
