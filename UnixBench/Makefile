##############################################################################
#	UnixBench v5.1.3
#  Based on The BYTE UNIX Benchmarks - Release 3
#          Module: Makefile   SID: 3.9 5/15/91 19:30:15
#
##############################################################################
# Bug reports, patches, comments, suggestions should be sent to:
#	David C Niemi <niemi@tux.org>
#
# Original Contacts at Byte Magazine:
#	Ben Smith or Tom Yager at BYTE Magazine
#	bensmith@bytepb.byte.com    tyager@bytepb.byte.com
#
##############################################################################
#  Modification Log: 7/28/89 cleaned out workload files
#                    4/17/90 added routines for installing from shar mess
#                    7/23/90 added compile for dhrystone version 2.1
#                          (this is not part of Run file. still use old)
#                          removed HZ from everything but dhry.
#                          HZ is read from the environment, if not
#                          there, you must define it in this file
#                    10/30/90 moved new dhrystone into standard set
#                          new pgms (dhry included) run for a specified
#                          time rather than specified number of loops
#                    4/5/91 cleaned out files not needed for
#                          release 3 -- added release 3 files -ben
#                    10/22/97 added compiler options for strict ANSI C
#                          checking for gcc and DEC's cc on
#                          Digital Unix 4.x (kahn@zk3.dec.com)
#                    09/26/07 changes for UnixBench 5.0
#                    09/30/07 adding ubgears, GRAPHIC_TESTS switch
#                    10/14/07 adding large.txt
#                    01/13/11 added support for parallel compilation
#                    01/07/16 [refer to version control commit messages and
#                              cease using two-digit years in date formats]
##############################################################################

##############################################################################
# CONFIGURATION
##############################################################################

SHELL = /bin/sh

# GRAPHIC TESTS: Uncomment the definition of "GRAPHIC_TESTS" to enable
# the building of the graphics benchmarks.  This will require the
# X11 libraries on your system. (e.g. libX11-devel mesa-libGL-devel)
#
# Comment the line out to disable these tests.
# GRAPHIC_TESTS = defined

# Set "GL_LIBS" to the libraries needed to link a GL program.
GL_LIBS = -lGL -lXext -lX11


# COMPILER CONFIGURATION: Set "CC" to the name of the compiler to use
# to build the binary benchmarks.  You should also set "$cCompiler" in the
# Run script to the name of the compiler you want to test.
CC=gcc

# OPTIMISATION SETTINGS:
# Use gcc option if defined UB_GCC_OPTIONS via "Environment variable" or "Command-line arguments".
ifdef UB_GCC_OPTIONS
  OPTON = $(UB_GCC_OPTIONS)

else
  ## Very generic
  #OPTON = -O

  ## For Linux 486/Pentium, GCC 2.7.x and 2.8.x
  #OPTON = -O2 -fomit-frame-pointer -fforce-addr -fforce-mem -ffast-math \
  #	-m486 -malign-loops=2 -malign-jumps=2 -malign-functions=2

  ## For Linux, GCC previous to 2.7.0
  #OPTON = -O2 -fomit-frame-pointer -fforce-addr -fforce-mem -ffast-math -m486

  #OPTON = -O2 -fomit-frame-pointer -fforce-addr -fforce-mem -ffast-math \
  #	-m386 -malign-loops=1 -malign-jumps=1 -malign-functions=1

  ## For Solaris 2, or general-purpose GCC 2.7.x
  #OPTON = -O2 -fomit-frame-pointer -fforce-addr -ffast-math -Wall

  ## For Digital Unix v4.x, with DEC cc v5.x
  #OPTON = -O4
  #CFLAGS = -DTIME -std1 -verbose -w0

  ## gcc optimization flags
  ## (-ffast-math) disables strict IEEE or ISO rules/specifications for math funcs
  OPTON = -O3 -ffast-math

  ## OS detection.  Comment out if gmake syntax not supported by other 'make'. 
  OSNAME:=$(shell uname -s)
  ARCH := $(shell uname -p)
  ifeq ($(OSNAME),Linux)
    # Not all CPU architectures support "-march" or "-march=native".
    #   - Supported    : x86, x86_64, ARM, AARCH64, etc..
    #   - Not Supported: RISC-V, IBM Power, etc...
    ifneq ($(ARCH),$(filter $(ARCH),ppc64 ppc64le))
        OPTON += -march=native -mtune=native
    else
        OPTON += -mcpu=native -mtune=native
    endif
  endif

  ifeq ($(OSNAME),Darwin)
    # (adjust flags or comment out this section for older versions of XCode or OS X)
    # (-mmacosx-versin-min= requires at least that version of SDK be installed)
    ifneq ($(ARCH),$(filter $(ARCH),ppc64 ppc64le))
        OPTON += -march=native -mmacosx-version-min=10.10
    else
        OPTON += -mcpu=native
    endif
    #http://stackoverflow.com/questions/9840207/how-to-use-avx-pclmulqdq-on-mac-os-x-lion/19342603#19342603
    CFLAGS += -Wa,-q
  endif

endif


## generic gcc CFLAGS.  -DTIME must be included.
CFLAGS += -Wall -pedantic $(OPTON) -I $(SRCDIR) -DTIME


##############################################################################
# END CONFIGURATION
##############################################################################


# local directories
PROGDIR = ./pgms
SRCDIR = ./src
TESTDIR = ./testdir
RESULTDIR = ./results
TMPDIR = ./tmp
# other directories
INCLDIR = /usr/include
LIBDIR = /lib
SCRIPTS = unixbench.logo multi.sh tst.sh index.base
SOURCES = arith.c big.c context1.c \
	dummy.c execl.c \
	fstime.c hanoi.c \
	pipe.c spawn.c \
	syscall.c looper.c timeit.c time-polling.c \
	dhry_1.c dhry_2.c dhry.h whets.c ubgears.c
TESTS = sort.src cctest.c dc.dat large.txt

ifneq (,$(GRAPHIC_TESTS))
GRAPHIC_BINS = $(PROGDIR)/ubgears
else
GRAPHIC_BINS =
endif

# Program binaries.
BINS = $(PROGDIR)/arithoh $(PROGDIR)/register $(PROGDIR)/short \
	$(PROGDIR)/int $(PROGDIR)/long $(PROGDIR)/float $(PROGDIR)/double \
	$(PROGDIR)/hanoi $(PROGDIR)/syscall $(PROGDIR)/context1 \
	$(PROGDIR)/pipe $(PROGDIR)/spawn $(PROGDIR)/execl \
	$(PROGDIR)/dhry2 $(PROGDIR)/dhry2reg  $(PROGDIR)/looper \
	$(PROGDIR)/fstime $(PROGDIR)/whetstone-double $(GRAPHIC_BINS)
## These compile only on some platforms...
# $(PROGDIR)/poll $(PROGDIR)/poll2 $(PROGDIR)/select

# Required non-binary files.
REQD = $(BINS) $(PROGDIR)/unixbench.logo \
	$(PROGDIR)/multi.sh $(PROGDIR)/tst.sh $(PROGDIR)/index.base \
	$(PROGDIR)/gfx-x11 \
	$(TESTDIR)/sort.src $(TESTDIR)/cctest.c $(TESTDIR)/dc.dat \
	$(TESTDIR)/large.txt

# ######################### the big ALL ############################
all:
## Ick!!!  What is this about???  How about let's not chmod everything bogusly.
#	@chmod 744 * $(SRCDIR)/* $(PROGDIR)/* $(TESTDIR)/* $(DOCDIR)/*
	$(MAKE) distr
	$(MAKE) programs

# ####################### a check for Run ######################
check: $(REQD)
	$(MAKE) all
# ##############################################################
# distribute the files out to subdirectories if they are in this one
distr:
	@echo "Checking distribution of files"
# scripts
	@if  test ! -d  $(PROGDIR) \
        ; then  \
           mkdir $(PROGDIR) \
           ; mv $(SCRIPTS) $(PROGDIR) \
        ; else \
           echo "$(PROGDIR)  exists" \
        ; fi
# C sources
	@if  test ! -d  $(SRCDIR) \
        ; then  \
           mkdir $(SRCDIR) \
           ; mv $(SOURCES) $(SRCDIR) \
        ; else \
           echo "$(SRCDIR)  exists" \
        ; fi
# test data
	@if  test ! -d  $(TESTDIR) \
        ; then  \
           mkdir $(TESTDIR) \
           ; mv $(TESTS) $(TESTDIR) \
        ; else \
           echo "$(TESTDIR)  exists" \
        ; fi
# temporary work directory
	@if  test ! -d  $(TMPDIR) \
        ; then  \
           mkdir $(TMPDIR) \
        ; else \
           echo "$(TMPDIR)  exists" \
        ; fi
# directory for results
	@if  test ! -d  $(RESULTDIR) \
        ; then  \
           mkdir $(RESULTDIR) \
        ; else \
           echo "$(RESULTDIR)  exists" \
        ; fi

.PHONY: all check distr programs run clean spotless

programs: $(BINS)

# (use $< to link only the first dependency, instead of $^,
#  since the programs matching this pattern have only
#  one input file, and others are #include "xxx.c"
#  within the first.  (not condoning, just documenting))
# (dependencies could be generated by modern compilers,
#  but let's not assume modern compilers are present)
$(PROGDIR)/%:
	$(CC) -o $@ $(CFLAGS) $< $(LDFLAGS)

# Individual programs
# Sometimes the same source file is compiled in different ways.
# This limits the 'make' patterns that can usefully be applied.

$(PROGDIR)/arithoh:  $(SRCDIR)/arith.c $(SRCDIR)/timeit.c
$(PROGDIR)/arithoh:  CFLAGS += -Darithoh
$(PROGDIR)/register: $(SRCDIR)/arith.c $(SRCDIR)/timeit.c
$(PROGDIR)/register: CFLAGS += -Ddatum='register int'
$(PROGDIR)/short:    $(SRCDIR)/arith.c $(SRCDIR)/timeit.c
$(PROGDIR)/short:    CFLAGS += -Ddatum=short
$(PROGDIR)/int:      $(SRCDIR)/arith.c $(SRCDIR)/timeit.c
$(PROGDIR)/int:      CFLAGS += -Ddatum=int
$(PROGDIR)/long:     $(SRCDIR)/arith.c $(SRCDIR)/timeit.c
$(PROGDIR)/long:     CFLAGS += -Ddatum=long
$(PROGDIR)/float:    $(SRCDIR)/arith.c $(SRCDIR)/timeit.c
$(PROGDIR)/float:    CFLAGS += -Ddatum=float
$(PROGDIR)/double:   $(SRCDIR)/arith.c $(SRCDIR)/timeit.c
$(PROGDIR)/double:   CFLAGS += -Ddatum=double

$(PROGDIR)/poll:     $(SRCDIR)/time-polling.c
$(PROGDIR)/poll:     CFLAGS += -DUNIXBENCH -DHAS_POLL
$(PROGDIR)/poll2:    $(SRCDIR)/time-polling.c
$(PROGDIR)/poll2:    CFLAGS += -DUNIXBENCH -DHAS_POLL2
$(PROGDIR)/select:   $(SRCDIR)/time-polling.c
$(PROGDIR)/select:   CFLAGS += -DUNIXBENCH -DHAS_SELECT

$(PROGDIR)/whetstone-double: $(SRCDIR)/whets.c
$(PROGDIR)/whetstone-double: CFLAGS += -DDP -DGTODay -DUNIXBENCH
$(PROGDIR)/whetstone-double: LDFLAGS += -lm

$(PROGDIR)/pipe: $(SRCDIR)/pipe.c $(SRCDIR)/timeit.c

$(PROGDIR)/execl: $(SRCDIR)/execl.c $(SRCDIR)/big.c

$(PROGDIR)/spawn: $(SRCDIR)/spawn.c $(SRCDIR)/timeit.c

$(PROGDIR)/hanoi: $(SRCDIR)/hanoi.c $(SRCDIR)/timeit.c

$(PROGDIR)/fstime: $(SRCDIR)/fstime.c

$(PROGDIR)/syscall: $(SRCDIR)/syscall.c $(SRCDIR)/timeit.c

$(PROGDIR)/context1: $(SRCDIR)/context1.c $(SRCDIR)/timeit.c

$(PROGDIR)/looper: $(SRCDIR)/looper.c $(SRCDIR)/timeit.c

$(PROGDIR)/ubgears: $(SRCDIR)/ubgears.c
$(PROGDIR)/ubgears: LDFLAGS += -lm $(GL_LIBS)

$(PROGDIR)/dhry2: CFLAGS += -DHZ=${HZ}
$(PROGDIR)/dhry2: $(SRCDIR)/dhry_1.c $(SRCDIR)/dhry_2.c \
                  $(SRCDIR)/dhry.h $(SRCDIR)/timeit.c
	$(CC) -o $@ ${CFLAGS} $(SRCDIR)/dhry_1.c $(SRCDIR)/dhry_2.c

$(PROGDIR)/dhry2reg: CFLAGS += -DHZ=${HZ} -DREG=register
$(PROGDIR)/dhry2reg: $(SRCDIR)/dhry_1.c $(SRCDIR)/dhry_2.c \
                     $(SRCDIR)/dhry.h $(SRCDIR)/timeit.c
	$(CC) -o $@ ${CFLAGS} $(SRCDIR)/dhry_1.c $(SRCDIR)/dhry_2.c

# Run the benchmarks and create the reports
run:
	sh ./Run

clean:
	$(RM) $(BINS) core *~ */*~

spotless:	clean
	$(RM) $(RESULTDIR)/* $(TMPDIR)/*

## END ##
