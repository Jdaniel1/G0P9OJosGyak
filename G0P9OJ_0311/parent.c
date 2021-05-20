#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t fork(void);

int main(void)
{
	pid_t pid;
	if ((pid = fork()) < 0)
	{
		printf("Fork fail");
		exit(0);
	} else if (pid == 0) execl("./child", "child", (char*)NULL);

	waitpid(pid, NULL, 0);
	return 0;
}
