/* this is the master project file that we will use to put everything together */

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
//Function Prototypes
int checkopt(int argc, char *argv[], char *file);
int stealthmodeon();
void simpSigHandler(int sigNum, char *file);
int stealthmodeoff();

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
				stealthmodeon(file);
			case 'c':
				printf("Cat Mode");
				if(argc > 3){
					printf("too many arguments");
                		}
        	}
	}
return 0;
}

void simpSigHandler(int sigNum, char *file){
        if(sigNum == SIGUSR1 && stealthflag == 0){
                stealthmodeon(file);
        }
        if(sigNum == SIGUSR1 && stealthflag == 1){
                stealthmodeoff(file);
        }
}

// Milestone 0
//
// Milestone 1
//
// Milestone 2 (Cat function - Reading in data from STDIO until EOF)
//
// Milestone 3 (Hiding Executable)
int stealthmodeon(char *ogfile){
        char buff[MAX_SIZE];
        int deletefile = 0;
        int pausePt = 0;
	int srcfd = open(ogfile, O_RDONLY);
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
        if((deletefile=unlink(ogfile)) == -1){
                perror("Error");
                return errno;
        }
        lseek(srcfd,0,SEEK_SET);
        fprintf(stdout,"Pause Point: netGoat is still open, but does not appear in ls listings\n");
        scanf("%d", &pausePt);
        stealthflag = 1;
        return 0;
}

int stealthmodeoff(char *ogfile){
        int dstfd = 0;
        char buff[MAX_SIZE];
	int srcfd = open(ogfile, O_RDONLY);
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
        stealthflag = 0;
        close(srcfd);
	return 0;
}


// Milestone 4
// 
// Milestone 5
//
// Milestone 6

int main(int argc, char *argv[]){
        char *ogfile = argv[0];
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
	return 0;
}
