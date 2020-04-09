/* This is our test file to test your milestones! */


//Required Libraries 
#include <getopt.h>
#include <getopt.h> // option checking
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> // error checking 
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

/******************************************************************************/

//Global Variable
#define MAX_SIZE 1024
#define MAX_LINE_LENGTH 1024
int stealthflag;
int srcfd;
char *ogfile;

/******************************************************************************/

//Function Prototypes
int checkopt(int argc, char *argv[], char *file);
int stealthmodeon(int srcfd);
void simpSigHandler(int sigNum);
int stealthmodeoff(int srcfd);
int myEcho();
int printFile(char *fileName);
int maketemp();

/******************************************************************************/

//Define Functions
int checkopt(int argc, char *argv[], char *file){
        int option = 0;
	while((option = getopt(argc, argv, "hscf:")) != -1){
                switch (option) {
                        case 'h':
                                printf("NAME\n");
				printf("\tnetGoat - cyber toolkit\n\n");
				printf("SYNOPSIS\n");
				printf("\tnetGoat -h\n\tnetGoat [-s] [-c] [-f <filename>]\n\n");
				printf("COMMANDS\n");
				printf("\th or no arguments: Displays this help page\n");
				printf("\ts: Stealth Mode - hides the program from ls command\n");
				printf("\tc: Cat Mode, Echo Version - will store your standard input until EOF (CTRL-D), then will write it back to standard output\n");
				printf("\tf: Cat Mode, File Version - will read data from a file and write to standard output.\n\n");
                                exit(0);
			case 's':
				printf("Stealth Mode\n");
				stealthmodeon(srcfd);
				break;
			case 'c':
				printf("Cat Mode\n");
				myEcho();	
				break;
			case 'f':
				printf("Cat Mode - Reading from file %s \n", argv[2]);
				if(argc > 3){
					printf("Too many arguments. Our program can only handle one file at a time...\n");
				}
				printFile(argv[2]);
				break;
			case '?':
				exit(-1);
        	}
	}
return 0;
}

int printFile(char *fileName){
	FILE *file; //declare the file
	char line[MAX_LINE_LENGTH]; //declare the line variable
	file = fopen(fileName,"r"); //open the file in read mode
	if (file == NULL){ //if the file name is not valid
		perror("Error: ");
		return 0; //end the function
	}
	while(fgets(line,MAX_LINE_LENGTH,file) != NULL){ //go through the lines of the file, as long as null isn't reached,
		printf("%s",line ); //print the line
	}
	return 0;
}

int myEcho(){
  char buff[MAX_SIZE];
  if(scanf("%1024c", buff) == EOF) {
  }

  printf("--------------------------\n%s",buff);

return 0;
}

void simpSigHandler(int sigNum){
        if(sigNum == SIGUSR1 && stealthflag == 1){
                write(1,"Stealth Mode Disabling...\n", 27);
		sleep(1);
		stealthmodeoff(srcfd);
		return;
        }
	if(sigNum == SIGUSR1 && stealthflag == 0){
                write(1, "Stealth Mode Enabling...\n", 25);
		sleep(1);
		stealthmodeon(srcfd);
        	return;
	}
	if(sigNum == SIGUSR2){
		maketemp();
		return;
	}
}

int maketemp(){
	char filename[] = "/var/tmp/netGoatXXXXXX";
	char buff[MAX_SIZE];
	int fd = mkstemp(filename);
	if(fd==-1){
		perror("Error:");
		return errno;
	}
	while(read(srcfd,buff,MAX_SIZE) != 0){
		write(fd,buff,MAX_SIZE);
	}
	int perm = fchmod(fd, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	if(perm==-1){
		perror("Error:");
		return errno;
	}
	return 0;
}

// Milestone 0
//
// Milestone 1
//
// Milestone 2 (Cat function - Reading in data from STDIO until EOF)
//
// Milestone 3 (Hiding Executable)
int stealthmodeon(int srcfd){
        char buff[MAX_SIZE];
        int deletefile = 0;
        if(srcfd < 0){
                perror("Error");
                return errno;
        }
        if(read(srcfd,buff,1)<0){
                perror("Error");
                return errno;
        }
        if((deletefile=unlink(ogfile)) == -1){
                perror("Error");
                return errno;
        }
        lseek(srcfd,0,SEEK_SET);
        printf("Stealth Mode is now on.\n");
	stealthflag = 1;
        return 0;
}

int stealthmodeoff(int srcfd){
        int dstfd = 0;
        char buff[MAX_SIZE];
        dstfd = open("netGoatTEST", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IXOTH);
        int num = 1;
        while(num!=0){
                num = read(srcfd,buff,MAX_SIZE);
                if(num<0){
                        perror("Error");
                        return errno;
                }
                write(dstfd,buff,num);
        }
	close(dstfd);
	printf("Stealth Mode is now off.\n");
        stealthflag = 0;
	return 0;
}


// Milestone 4
// 
// Milestone 5
//
// Milestone 6

/*************************************************************************/

int main(int argc, char *argv[]){
        ogfile = argv[0];
	srcfd = open(ogfile, O_RDONLY);
	if(argc==1){
		printf("\nNAME\n");
		printf("\tnetGoat - cyber toolkit\n\n");
		printf("SYNOPSIS\n");
		printf("\tnetGoat -h\n\tnetGoat [-s] [-c] [-f <filename>]\n\n");
		printf("COMMANDS\n");
		printf("\th or no arguments: Displays this help page\n\n");
		printf("\ts: Stealth Mode - hides the program from ls command\n\n");
		printf("\tc: Cat Mode, Echo Version - will store your standard input until EOF (CTRL-D), then will write it back to standard output\n\n");
		printf("\tf: Cat Mode, File Version - will read data from a file and write to standard output.\n\n");
		return 0;
	}
	if(checkopt(argc, argv, ogfile) != 0){
		perror("Error: ");
		return errno;
	}
        struct sigaction sigHandler;
        sigHandler.sa_handler = &simpSigHandler;
        sigHandler.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sigHandler, NULL);
	sigaction(SIGUSR2, &sigHandler, NULL);
	while(1){
		pause();
	}
	if(stealthflag==0){
		printf("Program is ending, taking stealth mode off.\n");
		stealthmodeoff(srcfd);
	}
	return 0;
}
