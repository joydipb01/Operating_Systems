# Custom PS Command - 19MCME08

This is a collection of simple programs to simulate the "ps" command in linux, by making use of the "/proc" file system.

## Contents

1. ps08.c - The main program which executes all the functions present in the other two .c files
2. setinfo.c - Prints the information with respect to each process, which serves as the output of the entire project. It displays 5 columns:
	- PID: The process ID of the given process
	- PPID: The process ID of the parent of the process in question
	- State: Whether it is Idle(I), Sleeping(S) or Running(R), among others
	- Files Open: The number of files open w.r.t the process. Obtained by reading the "fd" directory within each PID. In case the fd directory cannot be read, a '-' is shown
	- Command: The command pertaining to the process shown
3. processes.c - Provides information about the validity of the PID, and retrieving the process directory itself from the '/proc' file system

Modularity has been of prime importance while developing this project, so that the programs are more readable

## Exit Codes

The exit code pertaining to each execution of the project can be obtained by running the `echo $?` command on the kernel. While the error message is printed accordingly, the status codes used are given below:

0 = successful execution
1 = Couldn't open a file/Invalid PID
4 = Couldn't close a directory
6 = Couldn't open a directory

## Makefile

A Makefile has been provided with this project to make it easy for the user to run programs. The following commands can be run on the kernel:

`make run`: to execute the "ps08" executable
`make all`: to compile the programs
`make clean`: to clean the directory of the object files
