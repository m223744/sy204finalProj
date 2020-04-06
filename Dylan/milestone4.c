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

// Global Variables
int srcfd; 
int stealthflag;

// Function Prototypes

int stealthmodeon( int argc, char *argv[]);
void simpSigHandler(int sigNum);
int stealthmodeoff(int argc, char *argv[]);

// Define Functions 
void simpSigHandler(int sigNum){
	if(sigNum == SIGUSR1 && stealthflag = 0){
		stealthmodeon(argc, argv);
	}
	if(sigNum == SIGUSR1 && stealthflag = 1){
		stealthmoff(argc, argv);
	}
}

int stealthmodeon(int argc, char *argv[]){
	char buff[MAX_SIZE];
	srcfd = 0;
	int dstfd = 0;
	int i = 1;
	int deletefile = 0;
	int pausePt = 0;
	struct sigaction sigHandler;
	sigHandler.sa_handler = &simpSigHandler;
	sigHandler.sa_flags = SA_RESTART;
	srcfd = open(argv[0], O_RDONLY);
	if(srcfd < 0){
		perror("Error");
		return errno; 
	}
	if(read(srcfd,buff,1)<0){
		perror("Error");
		return errno;
	}
	fprintf(stdout,"Pause Point: netGoat appears in ls listing\n");
	scanf("%d", &pausePt);
	if((deletefile=unlink(argv[0])) == -1){
		perror("Error");
		return errno;
	}
	lseek(srcfd,0,SEEK_SET);
	fprintf(stdout,"Pause Point: netGoat is still open, but does not appear in ls listings\n");
	scanf("%d", &pausePt);
	stealthflag = 1;
	return 0;
}

int stealthmodeoff(int argc, char *argv[]){
	int dstfd = 0; 
	char buff[MAX_SIZE];
	dstfd = open("netGoat", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IXOTH);
	int num = 1;
	while(num!=0){
		num = read(srcfd,buff,MAX_SIZE);
		if(num<0){
			perror("Error");
			return errno;
		}
		write(dstfd,buff,num);
	}
	stealthflag = 0; 
	close(srcfd);
}
