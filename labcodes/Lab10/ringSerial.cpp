#include <stdio.h>
int main()
{
    const int np = 4;
    int token[np];
    token[0] = 100;
    printf("Name: NIVED KRISHNA 2021bcs0028\n");
    for (int i = 0; i < np; i++)
    {
        int nextProcess = (i + 1) % np;
        token[nextProcess] = token[i];
printf("Process %d received token value: %d and passed it to Process%d\n", i, token[i], nextProcess);
    }
    printf("Process 0 received the token value: %d from the last process.\n", token[0]);
    return 0;
}