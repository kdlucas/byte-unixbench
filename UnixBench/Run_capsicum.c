#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <time.h>

int iteration = 0;
char BIN_DIR[256] = "";
char CURRENT_PATH[256];

int option(int argc, char *argv[]){
	int opt;
	while ((opt = getopt(argc ,argv, "i:p:")) != -1){
		switch (opt) {
			case 'i':
				iteration = atoi(optarg);
				printf("iterations : %d\n", iteration);
				break;
		}
	}
	return 0;
}
extern char **environ;
int main(int argc, char *argv[]){
	struct timeval startTime, endTime;
	struct timeval allStartTime, allEndTime;
	//int iteration = 0;
	char pgms[6][256] = {
		"pipe",
		"syscall",
		"context1",
		"spawn",
		"execl",
		"fstime"
	};
	//default option
	char *options[6][3] = {
		{"10", NULL},
		{"10", NULL},
		{"10", NULL},
		{"30", NULL},
		{"30", NULL},
		{"-c -t 30 -d './testDir' -b 1024 -m 2000", NULL},
	};


	option(argc, argv);
	if (!getcwd(CURRENT_PATH, sizeof(CURRENT_PATH))) return -1;
	printf("pwd: %s\n", CURRENT_PATH);
	snprintf(CURRENT_PATH, sizeof CURRENT_PATH, "%s/capsicum_pgms", CURRENT_PATH);
	printf("UB_BINDIR: %s\n", CURRENT_PATH);
	setenv("UB_BINDIR", CURRENT_PATH, 1);

	gettimeofday(&allStartTime, 0);
	int i, j = 0;
	for (j = 0; j < 6; j++){
		int status;
		char binary[256] = "";
		snprintf(binary, sizeof binary, "%s/%s", CURRENT_PATH, pgms[j]);
		printf("binary %s\n", binary);
		
		char *binary_options[3]; 
		binary_options[0] = binary;
		binary_options[1] = options[j][0];
		binary_options[2] = NULL;
		printf("iterations: %d\n",iteration);
		for (i = 0; i < iteration; i++){
			pid_t pid = fork();
			gettimeofday(&startTime, NULL);
			//child process
			if (pid == 0){
				if(execve(binary_options[0], binary_options, environ)== -1){
					perror("execve");
				}
			}
			
			//parent process
			if (pid = waitpid(pid, &status, 0) < 0){
				perror("wait");
				return 1;
			}
			if (WIFEXITED(status)) {
				gettimeofday(&endTime, NULL);
				printf("%lf\n", (float)(endTime.tv_sec - startTime.tv_sec) + (float)(endTime.tv_usec - startTime.tv_usec)/100000);
			}
		}
		printf("------------------\n");
	}
	gettimeofday(&allEndTime, 0);
	
	printf("all bench time: %ld\n", (float)allEndTime.tv_sec - allStartTime.tv_sec);
	return 0;
}
