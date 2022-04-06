#include "pipex.h"

void    ft_init_struct(t_pipex *input, char **argv, char **envp)
{
    input->first_fd = open(argv[1], O_RDONLY);
    if (input->first_fd == -1)
            perror("error fd");
    input->second_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777); 
    if (input->second_fd == -1)
            perror("error fd");
    input->env = envp;
}

void    ft_child1_process(t_pipex *input, char **argv)
{
    int p_id1;

    p_id1 = fork();
    if (p_id1 == -1)
        perror("ERROR : Forking child process failed\n");
    if (p_id1 == 0)
    {
        input->cmd1_arg = ft_split(argv[2], ' ');
        close(input->fd_pipe[0]); // we don't use it
        //I want to write cmd1 result to fd_pipe[1]
        dup2(input->first_fd, 0);
        dup2(input->fd_pipe[1], 1); // duplicate & redirect to stdout
        // bc cmd1 output becomes stdoud de cmd1
        //close(input->fd_pipe[1]); // still open but we have our duplicate. don't need anymore. 
        if (input->cmd1_arg[0] && ft_check_one_path(input, 1))
        {
            //lorsque cette cmd va s'executer, l'output va etre ecrit dans pipe_fd[1]
            execve(ft_check_one_path(input, 1), input->cmd1_arg, input->env);
            ft_free(input->cmd1_arg);
        }
        else
            cmd_not_found(input->cmd1_arg, input);
    }
}

void    ft_child2_process(t_pipex *input, char **argv)
{
    int p_id2;
    
    p_id2 = fork();
    if (p_id2 == -1)
        perror("ERROR : Forking child process failed\n");
    if (p_id2 == 0)
    {    
        input->cmd2_arg = ft_split(argv[3], ' ');
        dup2(input->second_fd, 1); // duplicate file & redirect to stdout
        // Faire en sorte que le file en arg4 soit la nouvelle sortie
        close(input->fd_pipe[1]); // don't use it.
        dup2(input->fd_pipe[0], 0); // duplicate & redirect to stdin
        // Faire en sorte que l'entree soit pipe_fd[0] SOIT le result de cmd1
        //close(input->fd_pipe[0]);
        if (input->cmd2_arg[0] && ft_check_one_path(input, 2))
        {
            // lorsqu'on execute cette cmd ; l'output va etre ecrit dans argv4
            execve(ft_check_one_path(input, 2), input->cmd2_arg, input->env);
            ft_free(input->cmd2_arg);
        } 
        else
            cmd_not_found(input->cmd2_arg, input);
    }
}

int main(int argc, char **argv, char **envp)
{
    t_pipex *input;

    input = (t_pipex *)malloc(sizeof(t_pipex));
    if (argc != 5)
        ft_input_error(input);
    else 
    {
        if (pipe(input->fd_pipe) == -1)
            perror("ERROR : Something went wrong with pipe()\n");
        ft_init_struct(input, argv, envp);
        ft_child1_process(input, argv);
        ft_child2_process(input, argv);
        close(input->fd_pipe[0]);
        close(input->fd_pipe[1]);
        waitpid(-1, &input->first_fd, 0);
        waitpid(-1, &input->second_fd, 0);
        free(input);
        return (0);
    }       
}