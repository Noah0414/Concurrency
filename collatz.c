/*My name is Noah Cuevas and my panther ID is 6819849
This program will take an iput from a user at the command line and input it into
a piecewise
function. Once the input has been taken in it will fork the process and then
output each process ID concurrently as well as the number coming from the output.
Once the child procsses finishes it will tell the parent that the process has
finished.
Once both finish it will let the user know that both children process have
finished and exit the code
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char **argv[])
{  
    //Initalizes the variables
    extern char *optarg;
	extern int optind;
    pid_t pid1;
    pid_t pid2;
    int n1;
    int n2;
  
    //this is where the user will input their number
	static char usage[] = "Usage: collatz %s\n";

    // these are the arguments after the command-line options 
    if (optind < argc)	
		for (; optind < argc; optind++)
      {
			n1 = atoi(argv[optind]);
            n2 = n1 +4;
        }
	else {
		printf("no arguments left to process\n");
	}
    printf("This is the Parent waiting!\n");
    // First fork process running
    pid1 = fork();
    // Checks to see if the fork failed
    if (pid1 < 0)
    {
        fprintf(stderr, "The Fork Failed");
        return 1;
    }
    // If the fork passes then it will print where child1 is and run
    // the piece wise function
    else if (pid1 == 0)
    {
        printf("From Child1, pid=%d, init: number=%d\n", getpid(), n1);
        // Loops the function till the child1 process finishes
        while (n1 != 1)
        {
            if (n1 % 2 == 0)
            {
                n1 = n1 / 2;
            }
            else
            {
                n1 = 3 * n1 + 1;
            }
            printf("From Child1,pid=%d: number=%d\n", getpid(), n1);
        }
        printf("From Child1, pid=%d Im done!\n", getpid(), n1);
    }
    // If the fork doesnt fall into the error or the child 1 it will fall here
    //  into the child 2 process
    else
    {
        // Checks to see if the second child process goes through
        pid2 = fork();
        if (pid2 < 0)
        {
            fprintf(stderr, "Fork Failed");
            return 1;
        }
        // If the fork passes then it will print where child2 is and run
        // the piece wise function
        else if (pid2 == 0)
        {
            printf("From Child2, pid=%d, init: number=%d\n", getpid(), n2);
            // Loops the function till the child1 process finishes
            while (n2 != 1)
            {
                if (n2 % 2 == 0)
                {
                    n2 = n2 / 2;
                }
                else
                {
                    n2 = 3 * n2 + 1;
                }
                printf("From Child2,pid=%d: number=%d\n", getpid(), n2);
            }
            printf("From Child2, pid=%d Im done!\n", getpid(), n2);
        }
        // Make the parent provess wait for the two children to finish
        // Once they both finish prints that the processes have finishhed and the
        //parent is finished else
        {
            wait(NULL);
            wait(NULL);
            printf("All my Children Compelte\n");
        }
    }
    return 0;
}