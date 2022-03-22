#include "pipex.h"

void ft_input_error()
{
    write(2,"Error Input\n./pipex [file1][cmd1][cmd2][file2]", 47);
    exit(EXIT_FAILURE);
}

/* void    ft_cmd_error(char *cmd)
{

} */