#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void do_child(char *cmd)
{
        char *argv[4];

	argv[0] = "/bin/sh";
	argv[1] = "-c";
	//argv[2] = "ls *.c | wc";
	argv[2] = cmd;
	argv[3] = NULL;
        execve(argv[0], argv, environ);
}

int mysystem(char *cmd){
        int child, status;

        if ((child = fork()) < 0) {
                perror("fork");
                exit(1);
        }

        if (child == 0) {
                do_child(cmd);
        } else {
                if (wait(&status) < 0) {
                        perror("wait");
                        exit(1);
                }
                //printf("The child (pid=%d) exited with status(%d).\n", child, WEXITSTATUS(status));
        }

        return 100;
}

int main(void){
	mysystem("ls *.c | wc");
	return EXIT_SUCCESS;
}
