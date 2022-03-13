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
    int     fd_pipe[2];
    int     first_fd;
    int     second_fd;
    int     status;
    char    *cmd;
    char    **paths;
    char    *cmd1;
    char    **cmd1_arg;
    char    *cmd2;
    char    **cmd2_arg;
    char    **env;
} t_pipex;

int main(int argc, char **argv, char **env);

/* Parsing */
int     ft_error(char *str);
char	*ft_strnstr(const char *big, const char *little, size_t len);
//char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void    ft_get_paths(t_pipex *input, char **env);
char    *ft_check_one_path(t_pipex *input, int index);
void	ft_free(char **args);
size_t	ft_strlen(const char *s);

/* Pipex */

#endif