#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int pipeArr[2];
    if (pipe(pipeArr) < 0)
    {
        perror("HIBA");
        exit(1);
    }

    int pid = fork();
    if (pid < 0)
        exit(2);

    if (pid == 0)
    {
        write(pipeArr[1], "OYFTRQ", 128);
    } else if (pid > 0)
    {
        wait(NULL);

        char szBuffer[128];
        read(pipeArr[0], szBuffer, sizeof(szBuffer));
        printf("%s\n", szBuffer);
    }

    return 0;
}
