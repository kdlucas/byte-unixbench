/*******************************************************************************
 *  The BYTE UNIX Benchmarks - Release 3
 *          Module: spawn.c   SID: 3.3 5/15/91 19:30:20
 *
 *******************************************************************************
 * Bug reports, patches, comments, suggestions should be sent to:
 *
 *	Ben Smith, Rick Grehan or Tom Yagerat BYTE Magazine
 *	ben@bytepb.byte.com   rick_g@bytepb.byte.com   tyager@bytepb.byte.com
 *
 *******************************************************************************
 *  Modification Log:
 *  $Header: spawn.c,v 3.4 87/06/22 14:32:48 kjmcdonell Beta $
 *  August 29, 1990 - Modified timing routines (ty)
 *  October 22, 1997 - code cleanup to remove ANSI C compiler warnings
 *                     Andy Kahn <kahn@zk3.dec.com>
 *
 ******************************************************************************/
char SCCSid[] = "@(#) @(#)spawn.c:3.3 -- 5/15/91 19:30:20";
/*
 *  Process creation
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "timeit.c"

unsigned long iter;

void report()
{
	fprintf(stderr,"COUNT|%lu|1|lps\n", iter);
	exit(0);
}

int main(argc, argv)
int	argc;
char	*argv[];
{
	int	slave, duration;
	int	status;

	if (argc != 2) {
		fprintf(stderr,"Usage: %s duration \n", argv[0]);
		exit(1);
	}

	duration = atoi(argv[1]);

	iter = 0;
	wake_me(duration, report);

	while (1) {
		if ((slave = fork()) == 0) {
			/* slave .. boring */
#if debug
			printf("fork OK\n");
#endif
			/* kill it right away */
			exit(0);
		} else if (slave < 0) {
			/* woops ... */
			fprintf(stderr,"Fork failed at iteration %lu\n", iter);
			perror("Reason");
			exit(2);
		} else
			/* master */
			wait(&status);
		if (status != 0) {
			fprintf(stderr,"Bad wait status: 0x%x\n", status);
			exit(2);
		}
		iter++;
#if debug
		printf("Child %d done.\n", slave);
#endif
		}
}
