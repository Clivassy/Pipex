#include "pipex.h"

void    ft_get_paths(t_pipex *input, char **env)
{
    int     i;

    i = 0;
    while (!ft_strnstr(input->env[i], "PATH", 4))
        i++;
    input->paths = ft_split(input->env[i] + 5, ':');
}

char    *ft_check_one_path(t_pipex *input, int index)
{
    char    *path;
    char    *end_slash_path;
    int     i;

    if (index == 1)
        input->cmd = input->cmd1_arg[0];
    if (index == 2)
        input->cmd = input->cmd2_arg[0];
    if (ft_strnstr(input->cmd, "/", ft_strlen(input->cmd)))
        return (input->cmd);
    //printf("%s\n", input->cmd);
    ft_get_paths(input, input->env);
    //printf("%s\n", input->cmd);
    i = -1;
    while (input->paths[++i])
    {   
        end_slash_path = ft_strjoin(input->paths[i], "/");
        //printf("%s\n", end_slash_path);
        //printf("%s\n", input->cmd);
        path = ft_strjoin(end_slash_path, input->cmd);
        printf("%s\n", path);
        if (!access (path, F_OK)) 
        {
            ft_free(input->paths);
            return (path);
        }
        free(path);
    }
    ft_free(input->paths);
    return (0);
}
