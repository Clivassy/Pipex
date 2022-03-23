#include "pipex.h"

<<<<<<< HEAD
/* Get PATHS*/
=======
/* Get all paths of the env */ 
>>>>>>> 9361d78e5786f2f0b44732c8c620e5aaf7bb4a49
void    ft_get_paths(t_pipex *input)
{
    int     i;

    i = 0;
    while (!ft_strnstr(input->env[i], "PATH", 4))
        i++;
    input->paths = ft_split(input->env[i] + 5, ':');
}

<<<<<<< HEAD
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
    if (ft_strnstr(input->cmd, "/", ft_strlen(input->cmd)))
        return (input->cmd);
    ft_get_paths(input);
=======
/* init the cmd given the input*/
void    ft_check_cmd(t_pipex *input, int index)
{
    if (index == 1)
        input->cmd = input->cmd1_arg[0];
    if (index == 2)
        input->cmd = input->cmd2_arg[0];
}

char    ft_exist(t_pipex *input, char *path)
{
    char    *end_slash_path;
    int i;
    
>>>>>>> 9361d78e5786f2f0b44732c8c620e5aaf7bb4a49
    i = -1;
    while (input->paths[++i])
    {   
        end_slash_path = ft_strjoin(input->paths[i], "/");
        path = ft_strjoin(end_slash_path, input->cmd);
        if (!access (path, F_OK)) 
        {
            ft_free(input->paths);
            return (path);
        }
        free(path);
    }
}

char    *ft_check_one_path(t_pipex *input, int index)
{
    char    *path;

    ft_check_cmd(input, index);
    if (ft_strnstr(input->cmd, "/", ft_strlen(input->cmd)))
        return (input->cmd);
    ft_get_paths(input);
    path = ft_exist(input, path);
    ft_free(input->paths);
    return (0);
}
