#include "pipex.h"

void    ft_parsing(t_pipex *input)
{

}

int ft_error(char *str)
{
    printf("%s\n", str);
    return (0);
}

int main(int argc, char **argv, char **env)
{
    t_pipex *input;

    input = NULL;
    if (argc != 5)
        return(ft_error("wrong input\n"));
    else 
    {
        input = malloc(sizeof(t_pipex));
        if (pipe(input->fd) == -1)
            ft_error("Something went wrong with pipe()\n");
        //initialize all data of the struct
        // knowing that input is as follow :
        // <file1 cmd1 cmd2 file2>
        input->fd_child1 = open(argv[1], O_RDONLY);
        input->fd_child2 = open(argv[4], O_RDONLY);
        input->cmd1 = argv[2];
        input-> cmd2 = argv[3];
        // here check input : parsing (&input)
        // here call pipex function (&input)
        // close(input->fd_child1)
        // close(input->fd_child2)
        return(0);
    }       
}