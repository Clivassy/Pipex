/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbatoro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:35:37 by jbatoro           #+#    #+#             */
/*   Updated: 2022/03/29 16:39:31 by jbatoro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"


void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

void	ft_fd_error(char *file, char *error)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}

void	ft_init_struct(t_pipex *input, char **argv, char **envp)
{
	input->first_fd = open(argv[1], O_RDONLY);
	if (input->first_fd == -1)
		error(argv[1], strerror(errno));
	input->second_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (input->second_fd == -1)
		//ft_error(input);
	input->env = envp;
}

void	ft_child1_process(t_pipex *input, char **argv)
{
	if (dup2(input->fd_pipe[1], 1) == -1)
		ft_error(input);
	close(input->fd_pipe[0]);
	if (dup2(input->first_fd, 0) == -1)
		ft_error(input);
	input->cmd1_arg = ft_split(argv[2], ' ');
	if (input->cmd1_arg[0] && ft_check_one_path(input, 1))
	{
		execve(ft_check_one_path(input, 1), input->cmd1_arg, input->env);
		ft_free(input->cmd1_arg);
	}
	else
		ft_cmd_error(input->cmd1_arg, input);
}

void	ft_child2_process(t_pipex *input, char **argv)
{
	if (dup2(input->fd_pipe[0], 0) == -1)
		ft_error(input);
	close(input->fd_pipe[1]);
	if (dup2(input->second_fd, 1) == -1)
		ft_error(input);
	input->cmd2_arg = ft_split(argv[3], ' ');
	if (input->cmd2_arg[0] && ft_check_one_path(input, 2))
	{
		execve(ft_check_one_path(input, 2), input->cmd2_arg, input->env);
		ft_free(input->cmd2_arg);
	}
	else
		ft_cmd_error(input->cmd2_arg, input);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*input;
	
	input = (t_pipex *)malloc(sizeof(t_pipex));
	if (argc != 5)
		ft_input_error(input);
	if (pipe(input->fd_pipe) == -1)
		ft_error(input);
	ft_init_struct(input, argv, envp);
	input->pid_1 = fork();
	if (input->pid_1 == -1)
		ft_error(input);
	if (input->pid_1 == 0)
		ft_child1_process(input, argv);
	input->pid_2 = fork();
	if (input->pid_2 == -1)
		ft_error(input);
	if (input->pid_2 == 0)
		ft_child2_process(input, argv);
	ft_close_pipes(input);
	waitpid(-1, &input->first_fd, 0);
	waitpid(-1, &input->second_fd, 0);
	ft_close_fds(input);
	free(input);
	return (0);
}
