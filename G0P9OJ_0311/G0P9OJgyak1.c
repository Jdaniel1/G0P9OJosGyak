#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    if (!system("dir"))
    {
        for (int i = 0; i < 3; i++)
        {
            printf("%i\n", i);
        }
    }

    system("color b");
    system("asd");
    return 0;
}
