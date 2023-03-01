#! /bin/sh
###############################################################################
#  The BYTE UNIX Benchmarks - Release 3
#          Module: tst.sh   SID: 3.4 5/15/91 19:30:24
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
ID="@(#)tst.sh:3.4 -- 5/15/91 19:30:24";
sort_src_content=$(cat sort.src)
printf "$sort_src_content%.0s\n" $(seq $1) | sort > sort.src.$$
od sort.$$ | sort -n -k 1 > od.$$
grep the sort.$$ | tee grep.$$ | wc > wc.$$
rm sort.$$ grep.$$ od.$$ wc.$$
