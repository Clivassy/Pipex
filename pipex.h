#ifndef PIPEX_H
#define PIPEX_H

# include <stdio.h>
# include <time.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_pipex
{
    int     fd_child1;
    int     fd_child2;
    int     fd[2];
    int     fd_status;
    char    *cmd1;
    char    *cmd2;
    char    **cmd1_arg;
    char    **cmd2_arg;
    char    **env;
} t_pipex;

int main(int argc, char **argv, char **env);

#endif