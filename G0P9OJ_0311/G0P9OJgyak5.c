#include <stdlib.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void exit(int status);
void abort(void);

int main(void)
{
    if ((pid = fork()) < 0) perror("fork error");
    else if (pid == 0) exit(7);

    if (wait(&status) != pid)
        perror("wait error");

    if (WIFEXITED(status))
        printf("Normal return value = %d\n", WEXITSTATUS(status));

    if ( (pid = fork()) < 0) perror("fork error");
    else if (pid == 0)
    abort();

    if (wait(&status) != pid) perror("wait error");
    if (WIFSIGNALED(status))
        printf("Abnormal return value = %d\n", WTERMSIG(status));
        
    return 0;	
}
