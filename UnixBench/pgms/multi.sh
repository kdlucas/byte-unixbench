#! /bin/sh
###############################################################################
#  The BYTE UNIX Benchmarks - Release 3
#          Module: multi.sh   SID: 3.4 5/15/91 19:30:24
#          
###############################################################################
# Bug reports, patches, comments, suggestions should be sent to:
#
#	Ben Smith or Rick Grehan at BYTE Magazine
#	ben@bytepb.UUCP    rick_g@bytepb.UUCP
#
###############################################################################
#  Modification Log:
#
###############################################################################
ID="@(#)multi.sh:3.4 -- 5/15/91 19:30:24";
instance=1
sort_src=sort.src
times_of_sort_src=${TIMES_OF_SORT_SRC:-1}
if [ $times_of_sort_src -gt 1 ]; then
	for i in $(seq $times_of_sort_src); do combine_sort_src+=" $sort_src"; done
	cat $combine_sort_src > sort.src-alt.$$
	sort_src=sort.src-alt.$$
fi

while [ $instance -le $1 ]; do
	/bin/sh "$UB_BINDIR/tst.sh" $sort_src &
	instance=$(($instance + 1))
done
wait

if [ $times_of_sort_src -gt 1 ]; then
	rm $sort_src
fi

