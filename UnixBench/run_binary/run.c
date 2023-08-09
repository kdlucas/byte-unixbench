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
//default option
char *options[6][3] = {
	{"pipe", "10", NULL},
	{"syscall", "10", NULL},
	{"context1", "10", NULL},
	{"spawn", "30", NULL},
	{"execl", "30", NULL},
	{"fstime", "-c -t 30 -d './testDir' -b 1024 -m 2000", NULL},
};

char* result = "/home/mouse/byte-unixbench/UnixBench/run_binary/result";
	
int main(int argc, char *argv[]){
	struct timeval startTime, endTime;
	struct timeval allStartTime, allEndTime;
	int status;
	int iteration = 0;
	
	if (argc <= 3){
		printf("args\n");
		return 1;
	}
	
	iteration = argc[1];
	gettimeofday(&allStartTime, 0);
	int i, j = 0;
	for (j = 0; j < 6; j++){
		printf("program: %s\n",options[j][0]);
		for (i = 0; i < 10; i++){
			pid_t pid = fork();
			gettimeofday(&startTime, NULL);
			//child process
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
