/*******************************************************************************
 *  The BYTE UNIX Benchmarks - Release 3
 *          Module: named_pipe.c   SID: 0.1 -- 8/06/24 11:11:11
 *
 *******************************************************************************
 * Bug reports, patches, comments, suggestions should be sent to:
 *
 *    Ben Smith, Rick Grehan or Tom Yager
 *    ben@bytepb.byte.com   rick_g@bytepb.byte.com   tyager@bytepb.byte.com
 *
 *******************************************************************************
 *  Modification Log:
 *
 ******************************************************************************/
char SCCSid[] = "@(#) @(#)named_pipe.c:0.1 -- 8/06/24 11:11:11";
/*
 *  named_pipe  -- test single process named pipe throughput (no context switching)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "timeit.c"

unsigned long iter;
char fifo_name[] = "/tmp/test_fifoXXXXXX";

void report()
{
    fprintf(stderr,"COUNT|%ld|1|lps\n", iter);

    // Clean up
    unlink(fifo_name);

    exit(0);
}

int main(int argc, char *argv[])
{
    char buf[512];
    int fd_read, fd_write, duration;

    if (argc != 2) {
        fprintf(stderr,"Usage: %s duration\n", argv[0]);
        exit(1);
    }

    duration = atoi(argv[1]);

    // Generate a unique FIFO name
    if (mkstemp(fifo_name) == -1) {
        perror("mkstemp");
        exit(1);
    }

    // Remove the generated file and create a named pipe (FIFO) with the same name
    unlink(fifo_name);
    if (mkfifo(fifo_name, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    // Open the FIFO for reading and writing
    fd_read = open(fifo_name, O_RDONLY | O_NONBLOCK);
    if (fd_read == -1) {
        perror("open for read");
        exit(1);
    }

    fd_write = open(fifo_name, O_WRONLY | O_NONBLOCK);
    if (fd_write == -1) {
        perror("open for write");
        exit(1);
    }

    wake_me(duration, report);
    iter = 0;

    while (1) {
        if (write(fd_write, buf, sizeof(buf)) != sizeof(buf)) {
            if ((errno != EINTR) && (errno != 0))
                fprintf(stderr,"write failed, error %d\n", errno);
        }
        if (read(fd_read, buf, sizeof(buf)) != sizeof(buf)) {
            if ((errno != EINTR) && (errno != 0))
                fprintf(stderr,"read failed, error %d\n", errno);
        }
        iter++;
    }
}
