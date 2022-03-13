#include "pipex.h"

void    ft_get_paths(t_pipex *input, char **env)
{
    int     i;

    i = 0;
   // printf("%s\n", (*input)->env[i]);
    while (!ft_strnstr(input->env[i], "PATH", 4))
    {
            i++;
    }
    input->paths = ft_split(input->env[i] + 5, ':');
   /* printf("%s\n", (*input)->paths[0]);
    printf("%s\n", (*input)->paths[1]);
    printf("%s\n", (*input)->paths[2]); */
}

char    *ft_check_one_path(t_pipex *input, int index)
{
    char    *path;
    char    *end_slash_path;
    int     i;

    //printf("%s\n", input->cmd);
    if (index == 1)
        input->cmd = input->cmd1;
    if (index == 2)
        input->cmd = input->cmd2;
    //printf("%s\n", input->cmd);
    if (ft_strnstr(input->cmd, "/", ft_strlen(input->cmd)))
        return (input->cmd);
    //printf("%s\n", input->cmd);
    ft_get_paths(input, input->env);
  /* printf("%s\n", input->paths[0]);
    printf("%s\n", input->paths[1]);
    printf("%s\n", input->paths[2]); */
    //printf("%s\n", input->cmd);
    i = -1;
    while (input->paths[++i])
    {   
       // printf("%s\n", input->paths[i]);
        //get one path : on ajoute le / de fin
        end_slash_path = ft_strjoin(input->paths[i], "/");
        //printf("%s\n", end_slash_path);
        printf("%s\n", input->cmd);
        // joindre le path avec la commande
        path = ft_strjoin(end_slash_path, input->cmd); // ATTENTION AU STR_JOIN 
        //free (end_slash_path); // on ne va plus l'utiliser
        // car on va utiliser le path avec cmd
        // et on veut reutiliser la  variable vide 
        // en boucle, jusqu'a !input->path
       // printf("%s\n", path);
        if (!access (path, F_OK)) // F_OK == existence test
        // on check si le path existe
        {
            ft_free(input->paths);
            return (path);
        }
        free(path);
    }
    ft_free(input->paths);
    return (0);
}
