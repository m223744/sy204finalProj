/* This is Milestone 3 which enters the program into stealth mode. Coded will only be the portion of the milestone that will be copy pasted into the mainProj c file.
*/ 


//req libraries

#include <getopt.h> // option checking
#include <sys/types.h> 
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> // error checking 
#include <stdio.h> 

// Function Prototypes

int regfilecheck(char *filename);
int stealthmode( int argc, char *argv[]);

// Define Functions 


