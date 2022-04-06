#include "pipex.h"

/* Get PATHS*/
void    ft_get_paths(t_pipex *input)
{
    int     i;

    i = 0;
    while (!ft_strnstr(input->env[i], "PATH", 4))
        i++;
    input->paths = ft_split(input->env[i] + 5, ':');
}

/* Init the cmd given the input*/
void    ft_check_cmd(t_pipex *input, int index)
{
    if (index == 1)
        input->cmd = input->cmd1_arg[0];
    if (index == 2)
        input->cmd = input->cmd2_arg[0];
}

/* Check all paths*/
char    *ft_check_one_path(t_pipex *input, int index)
{
    char    *path;
    char    *end_slash_path;
    int     i;

    ft_check_cmd(input, index);
    ft_get_paths(input);
    i = -1;
    while (input->paths[++i])
    {   
        end_slash_path = ft_strjoin(input->paths[i], "/");
        path = ft_strjoin(end_slash_path, input->cmd);
        free(end_slash_path);
        if (access(path, F_OK) == 0) 
        {   
            ft_free(input->paths);
            return (path);
        }
        free(path);
    }
    ft_free(input->paths);
    return (0);
}