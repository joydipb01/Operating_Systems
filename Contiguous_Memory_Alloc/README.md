# Contiguous Memory Allocation Algorithms - 19MCME08

This is a collection of simple programs to to illustrate the various contiguous memory allocation algorithms. Each of them take inputs from a file, which is to be passed as a command line argument.

## Contents

1. The eponymous .c files demonstrating the respective memory allocation algorithms
2. me08.h - The header file comprising of the user-defined datatypes used for the programs

## Input file

It should be noted that the input file MUST be of the following order:

<Total_Memory><br>
<Number_of_holes><br>
<Hole_information_of_x_lines><br>
<Process_size_of_y_lines><br>

Here, `x` denotes the number of holes, while `y` denotes the number of processes

Hole information should be given as:

<Start_Address>, <Hole_Size>

## Exit Codes

The exit code pertaining to each execution of the project can be obtained by running the `echo $?` command on the kernel. While the error message is printed accordingly, the status codes used are given below:

0 = successful execution<br>
1 = Invalid argument count (cmd arguments)<br>
2 = Could not open file/File doesn't exist<br>
3 = Irregularity in input given in input file<br>

## Output

The output contains the columns `Process ID`, `Size (of the process)`, `Address where the process has been allocated`.
It is to be noted that the process ID of the file is in order of appearance of process size requirements.

Eg.: If the input is

600<br>
500<br>
400<br>

Then process 1 will have a size of 600, process 2 of 500 and so on.

`-1` under the allocation address column indicates that the process could not be allocated
