**UnixBench** is the original BYTE UNIX benchmark suite, updated and revised by many people over the years.

The purpose of UnixBench is to provide a basic indicator of the performance
of a Unix-like system; hence, multiple tests are used to test various
aspects of the system's performance.  These test results are then compared
to the scores from a baseline system to produce an index value, which is
generally easier to handle than the raw scores.  The entire set of index
values is then combined to make an overall index for the system.

Some very simple graphics tests are included to measure the 2D and 3D graphics performance of the system.

Multi-CPU systems are handled.  If your system has multiple CPUs, the
default behaviour is to run the selected
tests twice -- once with one copy of each test program running at a time,
and once with N copies, where N is the number of CPUs.  This is designed to
allow you to assess:

  * the performance of your system when running a single task
  * the performance of your system when running multiple tasks
  * the gain from your system's implementation of parallel processing

Do be aware that this is a system benchmark, not a CPU, RAM or disk benchmark.  The results will depend not only on your hardware, but on your operating system, libraries, and even compiler.

# History #
**UnixBench** was first started in 1983 at Monash University, as a simple synthetic benchmarking application. It was then taken and expanded by **_Byte Magazine_**. Linux mods by **Jon Tombs**, and original authors **Ben Smith**, **Rick Grehan**, and **Tom Yager**.The tests compare Unix systems by comparing their results to a set of scores set by running the code on a _benchmark_ system, which is a SPARCstation 20-61 (rated at 10.0).

**David C. Niemi** maintained the program for quite some time, and made some major modifications and updates, and produced **UnixBench 4**. He later gave the program to **Ian Smith** to maintain. Ian subsequently made some major changes and revised it from version 4 to version 5.

# Included Tests #

UnixBench consists of a number of individual tests that are targeted at specific areas. Here is a summary of what each test does:

## Dhrystone ##

Developed by _Reinhold Weicker_ in 1984. This benchmark is used to measure and compare the performance of computers. The test focuses on string handling, as there  are no floating point operations. It is heavily influenced by hardware and software design, compiler and linker options, code optimization, cache memory, wait states, and integer data types.

## Whetstone ##

This test measures the speed and efficiency of floating-point operations. This test contains several modules that are meant to represent a mix of operations typically performed in scientific applications. A wide variety of C functions including sin, cos, sqrt, exp, and log are used as well as integer and floating-point math operations, array accesses, conditional branches, and procedure calls. This test measure both integer and floating-point arithmetic.

## Execl Throughput ##

This test measures the number of execl calls that can be performed per second. Execl is part of the exec family of functions that replaces the current process image with a new process image. It and many other similar commands are front ends for the function execve().

## File Copy ##

This measures the rate at which data can be transferred from one file to another, using various buffer sizes. The file read, write and copy tests capture the number of characters that can be written, read and copied in a specified time (default is 10 seconds).

## Pipe Throughput ##

A pipe is the simplest form of communication between processes. Pipe throughtput is the number of times (per second) a process can write 512 bytes to a pipe and read them back. The pipe throughput test has no real counterpart in real-world programming.

## Pipe-based Context Switching ##

This test measures the number of times two processes can exchange an increasing integer through a pipe. The pipe-based context switching test is more like a real-world application. The test program spawns a child process with which it carries on a bi-directional pipe conversation.

## Process Creation ##

This test measure the number of times a process can fork and reap a child that immediately exits. Process creation refers to actually creating process control blocks and memory allocations for new processes, so this applies directly to memory bandwidth. Typically, this benchmark would be used to compare various implementations of operating system process creation calls.

## Shell Scripts ##

The shells scripts test measures the number of times per minute a process can start and reap a set of one, two, four and eight concurrent copies of a shell scripts where the shell script applies a series of transofrmation to a data file.

## System Call Overhead ##

This estimates the cost of entering and leaving the operating system kernel, i.e. the overhead for performing a system call. It consists of a simple program repeatedly calling the getpid (which returns the process id of the calling process) system call. The time to execute such calls is used to estimate the cost of entering and exiting the kernel.

## Graphical Tests ##

Both 2D and 3D graphical tests are provided; at the moment, the 3D suite in particular is very limited, consisting of the "ubgears" program.  These tests are intended to provide a very rough idea of the system's 2D and 3D graphics performance.  Bear in mind, of course, that the reported performance will depend not only on hardware, but on whether your system has appropriate drivers for it.