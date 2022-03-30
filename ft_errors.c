#include "pipex.h"

void ft_input_error(t_pipex *input)
{
    write(2,"Error Input\n./pipex [file1][cmd1][cmd2][file2]", 47);
    free(input);
	exit(EXIT_FAILURE);
}

void	cmd_not_found(char **cmd)
{
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 20);
	ft_free(cmd);
	exit(EXIT_FAILURE);
}