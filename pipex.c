/* 
--------------
General idea  
--------------
Read from "infile", execute cmd1 with "infile" 
as input, send the output to cmd2, which will
write to outfile".

pipe -> to send the output to of the first execve as input
to the second execve. 

fork -> to run two processes (i.e. to commands) in one single program.

dup2 -> to swap our files with stdin ans stdout

++ A bit of parsing. 

*/
# include <stdio.h>
# include <time.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

int main(int ac, char **av)
{
    int id = fork(); 
    // child process that has the same exact
    // memory as the main process. 
    int n; 
    if (id == 0)
        n = 1;
    else
        n = 6;
    if (id != 0)
        wait(&id); // wait the child process print his nb
        // before the parent process execute 
    int i;
    for (i = n; i < n + 5; i++)
    {
        printf("%d ", i);
        fflush(stdout);
    }
    if (id != 0)
       printf("\n");
    return (0);
}

/* int main(int ac, char **av)
{
    int id = fork();
    if (id != 0)
        fork();
    // prevent here : 
    // if we are in the main proces, ok we can fork.
    // BUT
    // if id is 0 (child process), it shouldn't call another fork.
    printf("Hello World\n");
    return (0);
} */

/* int main(int ac, char **av)
{
    int id = fork();
    // give birth to a child process
    // and start executing the following lines
   printf("Hello World from id : %d\n", id);
    // two separate id
    // one from the main process : id will be not 0. 
    // one from the child process : id always gonna be 0.
    if (id == 0)
        printf("--> We're in the child process\n");
    else
        printf("--> We're in the main process\n");
    return (0);
} */
