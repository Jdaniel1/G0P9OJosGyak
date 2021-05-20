#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define TMP "/tmp/OYFTRQ"

int main(void)
{
    mkfifo(TMP, 0666);
    int pid = fork();
    if (pid < 0)
        exit(2);

    int fileDesc;
    if (pid == 0)
    {
        fileDesc = open(TMP, O_WRONLY);

        char szInput[] = "Bemeneti szoveg";
        write(fileDesc, szInput, sizeof(szInput));
    } else if (pid > 0 )
    {
        fileDesc = open(TMP, O_RDONLY);

        char szBuffer[128];
        read(fileDesc, szBuffer, sizeof(szBuffer));
        printf("%s\n", szBuffer);
        close(fileDesc);
    }

    return 0;
}
