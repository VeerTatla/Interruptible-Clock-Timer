/*
* Veer Tatla cssc1153
* Josh Robey cssc1126
* CS570 Assignment 3
* aclock.c
*
* This program runs a clock and count down timer. 
*/
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "aclock.h"

#define DEFAULT 30
#define CHAR_BUFFER_SIZE 12
#define PIPE_SIZE 2 



//Arrays and time variables
int pfd1[PIPE_SIZE], pfd2[PIPE_SIZE];
char charbuf[CHAR_BUFFER_SIZE];
char timebuf[CHAR_BUFFER_SIZE];


	
void countdown_clock(int counttime)
{
    	//string signal to end process
	strcpy(charbuf, "end process");

    	printf("Child 2 (Countdown Clock) process executing...\n\n");
	printf("---------------------------------------------------------\n\n");

	//Close Pipes not used
    	close(pfd2[0]);
	close(pfd1[1]);    
    	close(pfd1[0]);    

    	//Countdown
    	while(counttime>0)
    	{		
        	//Seconds formatting
        	if(counttime > 9)
        	{
            		printf("Countdown: %d seconds\n", counttime);
            		//Send signal to child 1 process not to end
            		write(pfd2[1], "do not end",12);
            		//Countdown every second
            		sleep(1);
        	}
        	else
        	{
            		printf("Countdown: 0%d seconds\n", counttime);
            		//Send signal to child 1 process not to end
            		write(pfd2[1], "do not end",12);
            		//Countdown every second
			sleep(1);
        	}
        	counttime--;
    	}

    		//Notify other child to end and close pipe
    		write(pfd2[1], charbuf, sizeof(charbuf));
		close(pfd2[1]);
    

	
    	
    	printf("Count Down complete!\n\n");
	printf("---------------------------------------------------------\n\n");
	printf("End of Child 2 (Countdown Clock) process...\n");
    	exit(1);
}

void localtime_clock()
{
	
	
	//temp buffer to get termination string
	char str1[CHAR_BUFFER_SIZE];

	strcpy(str1, "end process");

	printf("Child 1 (Localtime Clock) process executing...\n");

    	time_t timenow;
    	struct tm* localtimenow;
	
    	//Close pipes not used by localtime_clock()
    	close(pfd1[0]);
    	close(pfd1[1]);
    	close(pfd2[1]);

	//Print local time
    	for(;;)
    	{

        	timenow = time ( NULL );
        	localtimenow = localtime ( &timenow );

		//read message from child 2 process
		int status = read(pfd2[0], charbuf, 12);

		//compare buffer
        	int return_value = strcmp(str1, charbuf);

		//if not end print current status and buffer
		if (return_value != 0)
		{
			
            		printf("Local time is currently ");
            		strftime(timebuf, 12, "%H:%M:%S", localtimenow);
            
            
            		//NON-FUNCTIONAL ALARM
            		/*
            		if(timenow == alarmClock)
            		{
                		printf("ALARM REACHED!");
            		}
            		*/

            		puts(timebuf);                      
          
            		//Ensure clock is shown every second
            		sleep(1);
		}

		//if end notification received
		if(return_value == 0)
        	{
			//close writing end
            		close(pfd2[0]);

            		//return back to parent
            		printf("End of Child 1 (Local Time Clock) process...\n\n");
			printf("---------------------------------------------------------\n\n");
            		exit(1);
        	}
    	}

}

int main(int argc, const char * argv[])
{
    	int time = DEFAULT;
	 
	
    	const char *alarm[CHAR_BUFFER_SIZE];
    
    	//Take countdown time from argument
    	if(argc == 2 || argc == 3)
    	{
        	time = atoi(argv[1]);
		
    	} 

    	//Open pipes for proccess communication
    	printf("\nOpening pipes...\n");
    	pipe(pfd1);
    	pipe(pfd2);
    	printf("Pipes opened, now creating child processes...\n\n");
     	//child 1
    	switch (fork())
    	{
        	//Error checking
        	case -1:
            	printf("Error forking Child 1.\n");
            	exit(1);
            
            	//Child 2 process
        	case 0:
            	localtime_clock();
            	exit(1);
            
        	default:
            	break;
    	}
    
    	//child 2
    	switch (fork())
    	{
        	//Error checking
        	case -1:
            	printf("Error forking Child 2.\n");
            	exit(1);
            
        	//Child 2 process
        	case 0:
            	countdown_clock(time);
            	exit(1);
            
        	default:
            	break;
    	}
    	
    	printf("Parent waiting for children completion...\n");

	//wait until child process is terminated
    	if (wait(NULL) == -1)
    	{
        	printf("Error wating, no child process has ended!\n");
        	exit(EXIT_FAILURE);
    	}
    	if (wait(NULL) == -1)
    	{
        	printf("Error wating, no child process has ended!\n");
        	exit(EXIT_FAILURE);
    	}

    	//Closing parent end of all pipes
    	printf("Parent closing pipes...\n");
    	close(pfd1[0]);
    	close(pfd1[1]);
    	close(pfd2[0]);
    	close(pfd2[1]);

    	//Exit
    	printf("Parent process finishing...\n");
    	printf("Exiting gracefully...\n\n");	
    	exit(EXIT_SUCCESS);

}
