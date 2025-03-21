#include <stdio.h>

int main()
{
    volatile int i;

    printf("%d", i);
    return 0;
}

// < in cat -e 
// ls > out && ls 