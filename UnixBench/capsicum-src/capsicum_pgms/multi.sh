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
work_factor=${MULTI_SH_WORK_FACTOR:-1}
if [ $work_factor -gt 1 ]; then
	inputs=
	for i in $(seq $work_factor); do inputs="$inputs $sort_src"; done
	cat $inputs > sort.src-alt.$$
	sort_src=sort.src-alt.$$
fi

while [ $instance -le $1 ]; do
	/bin/sh "$UB_BINDIR/tst.sh" $sort_src &
	instance=$(($instance + 1))
done
wait

if [ $work_factor -gt 1 ]; then
	rm $sort_src
fi
