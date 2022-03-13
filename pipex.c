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
    input->cmd1= argv[2];
    input->cmd2 = argv[3];
}

int main(int argc, char **argv, char **envp)
{
    t_pipex *input;

    input = NULL;
    input = (t_pipex *)malloc(sizeof(t_pipex));
    if (argc != 5)
        return(ft_error("wrong input"));
    else 
    {
        if (pipe(input->fd_pipe) == -1)
            ft_error("Something went wrong with pipe()");
        //printf("input ok\n");
        ft_init_struct(input, argv, envp);
        if (ft_check_one_path(input, 1))
            printf("CHECK OK");
        else
            perror("error");
        // get paths -> fct OK 
       /*  ft_get_paths(input); 
        int i = 0;
        while (input->paths[i])
        {
            printf("Path %d\n%s\n", i, input->paths[i]);
            i++;
        } */
        return (0);
    }       
}