/* this is the master project file that we will use to put everything together */

//Required Libraries 
#include <getopt.h>

//Function Prototypes
int checkopt(int argc, char *argv[]);

//Define Functions
int checkopt(int argc, char *argv[]){
        int option = 0;
        while((option = getopt(argc, argv, "hsc:")) != -1){
                switch (option) {
                        case 'h':
                                printf("Help Info \n");
                                return 0;
			case 's':
				printf("Stealth mode");
			case 'c':
				printf("Cat Mode");
				if(argc > 3){
					printf("too many arguments");
				file = argv[2];
                }
        }
        return 0;


// Milestone 0
//
// Milestone 1
//
// Milestone 2 (Cat function - Reading in data from STDIO until EOF)
//
// Milestone 3 (Hiding Executable)
//
// Milestone 4
// 
// Milestone 5
//
// Milestone 6
