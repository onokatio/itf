#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
        int file_fd;
        int file_fd2;

        if (argc != 3) {
                fprintf(stderr, "Usage: %s file_name redirect_file_name\n", argv[0]);
                exit(1);
        }

        file_fd = open(argv[1], O_RDONLY);
        if (file_fd < 0) {
                perror("open");
                exit(1);
        }

        file_fd2 = open(argv[2], O_WRONLY);
        if (file_fd < 0) {
                perror("open");
                exit(1);
        }

        close(0);
        if (dup2(file_fd, 0) < 0) {
                perror("dup2");
                close(file_fd);
                exit(1);
        }
        close(file_fd);

        close(1);
        if (dup2(file_fd2, 1) < 0) {
                perror("dup2");
                close(file_fd2);
                exit(1);
        }
        close(file_fd2);

        execlp("wc", "wc", NULL);

        return EXIT_FAILURE;
}
