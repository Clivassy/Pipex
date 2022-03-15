#include "pipex.h"

void ft_input_error()
{
    write(2,"Error Input\n./pipex [file1][cmd1][cmd2][file2]", 47);
    exit(EXIT_FAILURE);
}

void    ft_init_struct(t_pipex *input, char **argv, char **envp)
{
    input->first_fd = open(argv[1], O_RDONLY);
    if (input->first_fd == -1)
            perror("error fd");
    input->second_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0666); // can read or write but not exec
    if (input->second_fd == -1)
            perror("error fd");
    input->env = envp;
}

void    ft_child1_process(t_pipex *input, char **argv)
{
    int p_id1;

    p_id1 = fork();
    if (p_id1 == -1)
        perror("error fork");
    if (p_id1 == 0)
    {
        close(input->fd_pipe[0]); // we don't use it
        dup2(input->fd_pipe[1], 1); // duplicate & redirect to stdout
        close(input->fd_pipe[1]); // still open but we have our duplicate. don't need anymore. 
        input->cmd1_arg = ft_split(argv[2], ' ');
        if (input->cmd1_arg[0] && ft_check_one_path(input, 1))
        {
            execve(ft_check_one_path(input, 1), input->cmd1_arg, input->env);
            ft_free(input->cmd1_arg);
        }
        else
            perror("cmd not found : error");
    }
}

void    ft_child2_process(t_pipex *input, char **argv)
{
    int p_id2;
    
    p_id2 = fork();
    if (p_id2 == -1)
        perror("error fork");
    if (p_id2 == 0)
    {   
        //printf("%d\n",input->fd_pipe[0]);
        //printf("%d\n",input->second_fd);
        close(input->fd_pipe[1]); // don't use it. 
        dup2(input->second_fd, 1); // duplicate file & redirect to stdout
        dup2(input->fd_pipe[0], 0); // duplicate & redirect to stdin
        close(input->fd_pipe[0]);
        input->cmd2_arg = ft_split(argv[3], ' ');
        if (input->cmd2_arg[0] && ft_check_one_path(input, 2))
        {
            execve(ft_check_one_path(input, 2), input->cmd2_arg, input->env);
            ft_free(input->cmd2_arg);
        }
        else
            perror("cmd not found : error");
    }
}

int main(int argc, char **argv, char **envp)
{
    t_pipex *input;

    input = (t_pipex *)malloc(sizeof(t_pipex));
    if (argc != 5)
        ft_input_error();
    else 
    {
        if (pipe(input->fd_pipe) == -1)
            perror("Something went wrong with pipe()");
        ft_init_struct(input, argv, envp);
        ft_child1_process(input, argv);
        ft_child2_process(input, argv);
        close(input->fd_pipe[0]);
        close(input->fd_pipe[1]);
        // -1 == Wait for any child process.
        waitpid(input->fd_pipe[0], &input->status, 0);
        waitpid(input->fd_pipe[1], &input->status, 0);
        free(input);
        return (0);
    }       
}