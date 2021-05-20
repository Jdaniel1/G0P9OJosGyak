#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>

void TerminationHandler(int sig);

int main(void)
{
    if (signal(SIGTERM, TerminationHandler) == SIG_ERR)
    {
        printf("Nem sikerult handlert allitani a(z) \"SIGTERM\" jelre!\n");
        return 0;
    }

    while(1)
    {
        printf("Varakozas...\n");
        sleep(3);
    }

    return 0;
}
