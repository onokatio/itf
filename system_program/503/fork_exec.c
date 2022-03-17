#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

extern char **environ;

void sigsegv(int signum, siginfo_t *info, void *ctx){
	printf("Invalid memory access is detected.\n");
	printf("Memory address: %x",(int *)(info->si_addr));
	exit(1);
}

void sigfpe(int signum){
	printf("Zero division is detected.");
	exit(1);
}

int main(int argc, char *argv[]){

	struct sigaction sa_sigsegv;
	memset(&sa_sigsegv, 0, sizeof(sa_sigsegv));
	sa_sigsegv.sa_sigaction = sigsegv;
	sa_sigsegv.sa_flags = SA_SIGINFO;
	if (sigaction(SIGSEGV, &sa_sigsegv, NULL) < 0) {
	        perror("sigaction");
	        exit(1);
	}

	struct sigaction sa_sigfpe;
	memset(&sa_sigfpe, 0, sizeof(sa_sigfpe));
	sa_sigfpe.sa_handler = sigfpe;
	sa_sigfpe.sa_flags = 0;
	if (sigaction(SIGFPE, &sa_sigfpe, NULL) < 0) {
	        perror("sigaction");
	        exit(1);
	}

	if (argc != 2) exit(1);
	int num = strtol(argv[1],NULL,0);

	if(num == 1){
		char string[10];
		int index = 20000;
		char c = string[index];
		printf("%c",c);
	}else if(num == 2){
		int a = 100;
		int b = 0;
		int c = a / b;
		printf("%d %d %d",a,b,c);
	}

        return 0;
}
