#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
int pipe_fd_p2c[2];
int pipe_fd_c2p[2];
#define IN 1
#define OUT 0

void do_child(int num)
{
	close(pipe_fd_p2c[IN]);
	close(pipe_fd_c2p[OUT]);

	for(int i = 0; i < (num+1)/2;i++){
		char c;
		int writec,readc;
		while((readc = read(pipe_fd_p2c[OUT], &c, 1)) < 0){}
		printf("%c",'0' + i%10);
		fflush(stdout);
		if( (writec = write(pipe_fd_c2p[IN], "a", 1)) < 0){perror("write");}
	}
}

void do_parent(int num)
{
	close(pipe_fd_p2c[OUT]);
	close(pipe_fd_c2p[IN]);

	int writec,readc;
	if( (writec = write(pipe_fd_p2c[IN], "a", 1)) < 0){perror("write");}
	for(int i = 0; i < num/2;i++){
		char c;
		int writec,readc;
		while((readc = read(pipe_fd_c2p[OUT], &c, 1)) < 0){}
		printf("%c",'a' + i%26);
		fflush(stdout);
		if( (writec = write(pipe_fd_p2c[IN], "a", 1)) < 0){perror("write");}
	}
}

int main(int argc, char *argv[]){
        int child, status;

	if (pipe(pipe_fd_p2c) < 0) {
	        perror("pipe");
	        exit(1);
	}
	if (pipe(pipe_fd_c2p) < 0) {
	        perror("pipe");
	        exit(1);
	}

        if ((child = fork()) < 0) {
                perror("fork");
                exit(1);
        }

	int num = 60;
	num = strtol(argv[1],NULL,0);

        if (child == 0) {
                do_child(num);
        } else {
		do_parent(num);
                if (wait(&status) < 0) {
                        perror("wait");
                        exit(1);
                }
                //printf("The child (pid=%d) exited with status(%d).\n", child, WEXITSTATUS(status));
        }

        return 100;
}
