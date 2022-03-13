#include "pipex.h"

int ft_error(char *str)
{
    printf("%s\n", str);
    return (0);
}

void    ft_init_struct(t_pipex *input, char **argv, char **envp)
{
    input->first_fd = open(argv[1], O_RDONLY);
    if (input->first_fd == -1)
            ft_error("error fd");
    input->second_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (input->second_fd == -1)
            ft_error("error fd");
    input->env = envp;
}

void    ft_child_one_process(t_pipex *input, char **argv)
{
    int p_id;

    p_id = fork();
    if (p_id == -1)
        perror("error fork");
    if (p_id == 0)
    {
        input->cmd1_arg = ft_split(argv[2], ' ');
        //printf("%s\n", input->cmd1_arg[0]);
        close(input->fd_pipe[0]);
        //dup2(input->first_fd, 0);
        //dup2(input->fd_pipe[1], 1);
       // printf("%s\n", input->cmd1_arg[0]);
       //printf("OK");
        if (input->cmd1_arg[0] && ft_check_one_path(input, 1))
        {
            printf("OK");
            execve(ft_check_one_path(input, 1), input->cmd1_arg, input->env);
            ft_free(input->cmd1_arg);
        }
        else
            perror("error");
    }
}

int main(int argc, char **argv, char **envp)
{
    t_pipex *input;

    input = (t_pipex *)malloc(sizeof(t_pipex));
    if (argc != 5)
        return(ft_error("wrong input"));
    else 
    {
        if (pipe(input->fd_pipe) == -1)
            perror("Something went wrong with pipe()");
        ft_init_struct(input, argv, envp);
        ft_child_one_process(input, argv);
        // call child 2
        // close fd_pipe[0]
        // close fd_pipe[1]
        // wait child 1
        // wait child 2
        //ft_free(input);
        return (0);
    }       
}