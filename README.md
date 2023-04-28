# Banker's Algorithm

This C++ program implements the Banker's Algorithm for resource allocation. The program loads a file that contains resource allocation information for 5 processes and finds a safe sequence.

## Run the program
### On Linux:
Clone this repo and from the folder run the following
```
g++ main.cpp
./a.out
```
### On Windows:
```
Beats me
```
## Input File Format

The program reads the input from a file named "input.txt". The format of the input file is as follows:
- The first line of the file contains the available instances of resources A, B and C. These values are separated by spaces. Then it provides the max instances of A, B, and C.
- The next five lines of the file represent the current allocation of resources for each process. Each line contains the current allocation of resources A, B, and C for a particular process. These values are separated by spaces.
- The final five lines of the file represent the maximum demand of each process. Each line contains the maximum demand for resources A, B, and C for a particular process. These values are separated by spaces.

## Code Explanation

The program loads the input file and stores the information in arrays. Then, it calls the `bankers` function, which implements the Banker's Algorithm. If a safe sequence is found, the function returns true, and the safe sequence is stored in the `safeOrder` vector. Otherwise, the function returns false.

The `bankers` function takes three arrays as input:

- `work`: an array of available resources.
- `maxRes`: a 2D array of maximum resources needed by each process.
- `allocation`: a 2D array of currently allocated resources for each process.

The function then initializes an array called `finish`, which keeps track of whether a process has found a spot yet. It also initializes an array called `need`, which keeps track of the resources still needed by each process.

The function then enters a loop, which runs until a safe sequence has been found. Within this loop, the function checks each process to see if its resource needs can be satisfied. If a process can be accommodated, the function updates the `work` array and adds the process to the safe sequence. If no process can be accommodated, the function returns false, indicating that no safe sequence exists.

Finally, if a safe sequence is found, the `safeOrder` vector is printed to the console.

## Constants

The program defines the following constants:

- `PROCESS_COUNT`: the number of processes in the input file.
- `RESOURCE_COUNT`: the number of resource types in the input file.
- `ATTRIBUTE_COUNT`: the number of attributes for each resource in the input file.

## Globals

The program defines a global vector called `safeOrder`, which stores the safe sequence of processes.

## Functions

The program defines the following functions:

- `bankers`: the main function that implements the Banker's Algorithm.
- `main`: the function that loads the input file and calls the `bankers` function.