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

//Global Variable
#define MAX_SIZE 1024
int stealthflag;
int srcfd;
char *ogfile;

//Function Prototypes
int checkopt(int argc, char *argv[], char *file);
int stealthmodeon(int srcfd);
void simpSigHandler(int sigNum);
int stealthmodeoff(int srcfd);

//Define Functions
int checkopt(int argc, char *argv[], char *file){
        int option = 0;
	while((option = getopt(argc, argv, "hsc:")) != -1){
                switch (option) {
                        case 'h':
                                printf("Help Info \n");
                                return 0;
			case 's':
				printf("Stealth Mode\n");
				stealthmodeon(srcfd);
			case 'c':
				printf("Cat Mode");
        	}
	}
return 0;
}

void simpSigHandler(int sigNum){
        if(sigNum == SIGUSR1 && stealthflag == 1){
                write(1,"Stealth Mode Disabled\n", 23);
		stealthmodeoff(srcfd);
		return;
        }
	if(sigNum == SIGUSR1 && stealthflag == 0){
                write(1, "Stealth Mode Enabled\n", 21);
		stealthmodeon(srcfd);
        	return;
	}
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
        int pausePt = 0;
        if(srcfd < 0){
                perror("Error");
                return errno;
        }
        if(read(srcfd,buff,1)<0){
                perror("Error");
                return errno;
        }
        //fprintf(stdout,"Pause Point: netGoat appears in ls listing\n");
        //scanf("%d", &pausePt);
        if((deletefile=unlink(ogfile)) == -1){
                perror("Error");
                return errno;
        }
        lseek(srcfd,0,SEEK_SET);
        //fprintf(stdout,"Pause Point: netGoat is still open, but does not appear in ls listings\n");
        //scanf("%d", &pausePt);
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
        stealthflag = 0;
	return 0;
}


// Milestone 4
// 
// Milestone 5
//
// Milestone 6

int main(int argc, char *argv[]){
        ogfile = argv[0];
	srcfd = open(ogfile, O_RDONLY);
	if(argc==1){
		printf("Help Info\n");
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
	while(1){
		pause();
	}
	/*
	 *
	 * if(stealthflag=0){
		stealthmodeoff(srcfd);
		return 0;
	}

	above code should be the final call */
	
	return 0;
}
