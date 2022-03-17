#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

extern char **environ;

void sigint_action1(int signum){
}

void sigint_action2(int signum){
}

void do_child(int num,pid_t parent)
{
	struct sigaction sa_sigint;
	memset(&sa_sigint, 0, sizeof(sa_sigint));
	sa_sigint.sa_handler = sigint_action2;
	sa_sigint.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_sigint, NULL) < 0) {
	        perror("sigaction");
	        exit(1);
	}

	for(int i = 0; i < (num+1)/2;i++){
		pause();
		printf("%c",'0' + i%10);
		fflush(stdout);
		usleep(5000);
		if (kill(parent, SIGINT) < 0) {
		        perror("kill");
		        exit(1);
		}
	}
}

void do_parent(int num, pid_t child)
{
	struct sigaction sa_sigint;
	memset(&sa_sigint, 0, sizeof(sa_sigint));
	sa_sigint.sa_handler = sigint_action1;
	sa_sigint.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_sigint, NULL) < 0) {
	        perror("sigaction");
	        exit(1);
	}

	usleep(5000);
	kill(child,SIGINT);
	for(int i = 0; i < num/2;i++){
		pause();
		printf("%c",'a' + i%26);
		fflush(stdout);
		usleep(5000);
		if (kill(child, SIGINT) < 0) {
		        perror("kill");
		        exit(1);
		}
	}
}

int main(int argc, char *argv[]){
        int child, status;

	int num = 60;
	num = strtol(argv[1],NULL,0);

	pid_t parent = getpid();
	printf("%d\n",parent);

        if ((child = fork()) < 0) {
                perror("fork");
                exit(1);
        }

        if (child == 0) {
                do_child(num,parent);
        } else {
		printf("%d\n",child);
		do_parent(num,child);
                if (wait(&status) < 0) {
                        perror("wait");
                        exit(1);
                }
                //printf("The child (pid=%d) exited with status(%d).\n", child, WEXITSTATUS(status));
        }

        return 100;
}
