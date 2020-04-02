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

//Global Variable
#define MAX_SIZE 1024

//Function Prototypes
int checkopt(int argc, char *argv[]);
int stealthmode(int argc, char *argv[]);

//Define Functions
int checkopt(int argc, char *argv[]){
        int option = 0;
	while((option = getopt(argc, argv, "hsc:")) != -1){
                switch (option) {
                        case 'h':
                                printf("Help Info \n");
                                return 0;
			case 's':
				printf("Stealth Mode\n");
				stealthmode(argc,argv);
				return 0;
			case 'c':
				printf("Cat Mode");
				if(argc > 3){
					printf("too many arguments");
                		}
        	}
        return 0;
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
int stealthmode(int argc, char *argv[]){
        char buff[MAX_SIZE];
        int srcfd = 0;
        int dstfd = 0;
        int deletefile = 0;
        int pausePt = 0;
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
        close(srcfd);
        return 0;
}
// Milestone 4
// 
// Milestone 5
//
// Milestone 6

int main(int argc, char *argv[]){
	if(argc==1){
		printf("Help Info\n");
		return 0;
	}
	checkopt(argc, argv);
	return 0;
}
