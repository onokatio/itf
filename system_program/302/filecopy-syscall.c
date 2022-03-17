#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 100

int main(void)
{
        char c[BUFSIZE];
        int fps, fpd;
        int count;

        fps = open("src", O_RDONLY);
        if (fps < 0) {
                perror("open: src");
                exit(1);
        }

        fpd = open("dst", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fpd < 0) {
                perror("open: dst");
                close(fps);
                exit(1);
        }

        while ((count = read(fps, c, BUFSIZE)) > 0) {
                if (write(fpd, c, count) < 0) {
                        perror("write");
			close(fpd);
			close(fps);
                        exit(1);
                }
        }

        if (count < 0) {
                perror("read");
		close(fpd);
		close(fps);
                exit(1);
        }

        close(fpd);
        close(fps);

        return 0;
}
