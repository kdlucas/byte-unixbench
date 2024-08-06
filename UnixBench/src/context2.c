/*******************************************************************************
 *  The BYTE UNIX Benchmarks - Release 3
 *          Module: context2.c   SID: 0.1 8/06/24 11:11:11
 *
 *******************************************************************************
 * Bug reports, patches, comments, suggestions should be sent to:
 *
 *  Ben Smith, Rick Grehan or Tom Yager
 *  ben@bytepb.byte.com   rick_g@bytepb.byte.com   tyager@bytepb.byte.com
 *
 *******************************************************************************
 *
 ******************************************************************************/
char SCCSid[] = "@(#) @(#)context2.c:0.1 -- 8/06/24 11:11:11";
/*
 *  Context switching via synchronized named pipe i/o
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include "timeit.c"

unsigned long iter;

void report()
{
    fprintf(stderr, "COUNT|%lu|1|lps\n", iter);
    exit(0);
}

int main(int argc, char *argv[])
{
    int duration;
    unsigned long check;
    int fd1_read, fd1_write, fd2_read, fd2_write;
    ssize_t ret;
    char fifo1_name[] = "/tmp/test_fifo1XXXXXX";
    char fifo2_name[] = "/tmp/test_fifo2XXXXXX";

    if (argc != 2) {
        fprintf(stderr, "Usage: context duration\n");
        exit(1);
    }

    duration = atoi(argv[1]);

    // Generate unique FIFO names
    if (mkstemp(fifo1_name) == -1) {
        perror("mkstemp");
        exit(1);
    }
    if (mkstemp(fifo2_name) == -1) {
        perror("mkstemp");
        exit(1);
    }

    // Remove the generated files and create named pipes (FIFOs) with the same names
    unlink(fifo1_name);
    unlink(fifo2_name);
    if (mkfifo(fifo1_name, 0666) == -1) {
        perror("mkfifo1");
        exit(1);
    }
    if (mkfifo(fifo2_name, 0666) == -1) {
        perror("mkfifo2");
        exit(1);
    }

    /* set up alarm call */
    iter = 0;
    wake_me(duration, report);
    signal(SIGPIPE, SIG_IGN);

    if (fork()) {   /* parent process */
        /* initiator, write to fifo1 & read from fifo2 */
        fd1_write = open(fifo1_name, O_WRONLY);
        fd2_read = open(fifo2_name, O_RDONLY);
        if (fd1_write == -1 || fd2_read == -1) {
            perror("open parent");
            exit(1);
        }

        while (1) {
            if ((ret = write(fd1_write, (char *)&iter, sizeof(iter))) != sizeof(iter)) {
                if ((ret == -1) && (errno == EPIPE)) {
                    alarm(0);
                    report(); /* does not return */
                }
                if ((ret == -1) && (errno != 0) && (errno != EINTR))
                    perror("initiator write failed");
                exit(1);
            }
            if ((ret = read(fd2_read, (char *)&check, sizeof(check))) != sizeof(check)) {
                if ((ret == 0)) { /* end-of-stream */
                    alarm(0);
                    report(); /* does not return */
                }
                if ((ret == -1) && (errno != 0) && (errno != EINTR))
                    perror("initiator read failed");
                exit(1);
            }
            if (check != iter) {
                fprintf(stderr, "Initiator sync error: expect %lu, got %lu\n",
                    iter, check);
                exit(2);
            }
            iter++;
        }
    }
    else { /* child process */
        /* target, read from fifo1 & write to fifo2 */
        fd1_read = open(fifo1_name, O_RDONLY);
        fd2_write = open(fifo2_name, O_WRONLY);
        if (fd1_read == -1 || fd2_write == -1) {
            perror("open child");
            exit(1);
        }

        while (1) {
            if ((ret = read(fd1_read, (char *)&check, sizeof(check))) != sizeof(check)) {
                if ((ret == 0)) { /* end-of-stream */
                    alarm(0);
                    report(); /* does not return */
                }
                if ((ret == -1) && (errno != 0) && (errno != EINTR))
                    perror("target read failed");
                exit(1);
            }
            if (check != iter) {
                fprintf(stderr, "Target sync error: expect %lu, got %lu\n",
                    iter, check);
                exit(2);
            }
            if ((ret = write(fd2_write, (char *)&iter, sizeof(iter))) != sizeof(check)) {
                if ((ret == -1) && (errno == EPIPE)) {
                    alarm(0);
                    report(); /* does not return */
                }
                if ((ret == -1) && (errno != 0) && (errno != EINTR))
                    perror("target write failed");
                exit(1);
            }
            iter++;
        }
    }

    // Clean up
    unlink(fifo1_name);
    unlink(fifo2_name);
}

