#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	for (int i = 0; i < 5; i++)
	{
		printf("%i\n", i);
		sleep(1);
	}

	return 0;
}
