#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    char unixCmd[64];
    do {
        scanf("%s", unixCmd);
        system(unixCmd);
    } while(true);

    return 0;	
}
