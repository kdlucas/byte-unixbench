#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <time.h>

char pgms[5][100] = {
	"pipe",
	"syscall",
	"context1",
	"spawn",
	"execl",
	"fstime"
};
char *options[6][3] = {
	{"/home/mouse/byte-unixbench/UnixBench/capsicum_pgms/pipe", "10", NULL},
	{"/home/mouse/byte-unixbench/UnixBench/capsicum_pgms/syscall", "10", NULL},
	{"/home/mouse/byte-unixbench/UnixBench/capsicum_pgms/context1", "10", NULL},
	{"/home/mouse/byte-unixbench/UnixBench/capsicum_pgms/spawn", "30", NULL},
	{"/home/mouse/byte-unixbench/UnixBench/capsicum_pgms/execl", "30", NULL},
	{"/home/mouse/byte-unixbench/UnixBench/capsicum_pgms/fstime", "-c -t 30 -d './testDir' -b 1024 -m 2000", NULL},
};

char* result = "/home/mouse/byte-unixbench/UnixBench/run_binary/result";
	
int main(){
	struct timeval startTime, endTime;
	struct timeval allStartTime, allEndTime;
	int status;

	//child process
	gettimeofday(&allStartTime, 0);
	int i, j = 0;
	for (j = 0; j < 6; j++){
		for (i = 0; i < 1; i++){
			printf("program: %s\n",options[j][0]);
			pid_t pid = fork();
			gettimeofday(&startTime, NULL);
			if (pid == 0){
				if(execv(options[j][0], options[j]) == -1){
					perror("execve");
				}
			}
		//parent process
		waitpid(pid, &status, 0);
		gettimeofday(&endTime, NULL);
		printf("%lf\n", (float)(endTime.tv_sec - startTime.tv_sec) + (float)(endTime.tv_usec - startTime.tv_usec)/100000);
		}
		printf("------------------\n");
	}
	gettimeofday(&allEndTime, 0);
	
	printf("all bench time: %ld\n", (float)allEndTime.tv_sec - allStartTime.tv_sec);
	return 0;
}
