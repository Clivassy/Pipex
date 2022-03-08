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
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

int main(int ac, char **av)
{
    int fd[2];
    //fd[0] = read 
    //fd[1] = write
    if (pipe(fd) == -1)
    {
        printf("An error occured with opening the pipe\n");
        return (1);
    }
    int id = fork();
    if (id == 0)
    {
        close(fd[0]);
        int x;
        printf("input a number: ");
        scanf("%d", &x);
        if (write(fd[1], &x, sizeof(int) == -1))
        {
            printf("An error occured when writing the pipe\n");
            return (2);
        }
        close(fd[1]);
    }
    else 
    {
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int) == -1))
        {
            printf("An error occured when reading the pipe\n");
            return(3);
        }
        close(fd[0]);
        printf("Got from child process %d\n", y);
    }
    return (0);
}

/* int main(void) {
  printf("Main program started\n");
  char* argv[] = { "jim", "jams", NULL };
  char* envp[] = { "some", "environment", NULL };
  if (execve("./sub", argv, envp) == -1) // if it fails it return -1, otherwise it never return anything
    perror("Could not execve");
  return 1;
} */

/* int main(int ac, char **av)
{
    int id = fork(); 
    if (id == 0)
        sleep(1);
    printf("Current ID: %d , Parent ID: %d\n",
            getpid(), getppid()); // return 2 id 
    
    int res = wait(NULL); 
    if (res == -1)
        printf("No children to wait for\n");
    else
        printf("%d finished execution\n", res);
    return (0);
} */

/* int main(int ac, char **av)
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
} */

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


// fonction qui va parser l'input 

// 

/* int main(int argc, char **argv, char **env)
{
    // file1 cmd cmd file2 
    // == cmd file& | cmd file2
    // -> 4 arg / a.out
    if (argc != 5)
        return (0) // créer une fonction pour les erreurs. 
} */