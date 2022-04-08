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

/* void	ft_init_struct(t_pipex *input, char **argv, char **envp)
{
	input->first_fd = open(argv[1], O_RDONLY);
	if (input->first_fd == -1)
		ft_error(input);
	input->second_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (input->second_fd == -1)
		ft_error(input);
	input->env = envp;
} */

void	ft_child1_process(t_pipex *input, char **argv)
{
	int	p_id1;

	p_id1 = fork();
	if (p_id1 == -1)
	{
		free(input);
		perror("ERROR : Forking child process failed\n");
	}
	if (p_id1 == 0)
	{
		close(input->fd_pipe[0]);
		if (dup2(input->first_fd, 0) == -1)
			ft_error(input);
		if (dup2(input->fd_pipe[1], 1) == -1)
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
}

void	ft_child2_process(t_pipex *input, char **argv)
{
	int	p_id2;

	p_id2 = fork();
	if (p_id2 == -1)
	{
		free(input);
		perror("ERROR : Forking child process failed\n");
	}
	if (p_id2 == 0)
	{
		if (dup2(input->second_fd, 1) == -1)
			ft_error(input);
		close(input->fd_pipe[1]);
		if (dup2(input->fd_pipe[0], 0) == -1)
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
}

void	ft_close_fds(t_pipex *input)
{
	close(input->first_fd);
	close(input->second_fd);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*input;

	input = (t_pipex *)malloc(sizeof(t_pipex));
	if (argc != 5)
		ft_input_error(input);
	else
	{
		if (pipe(input->fd_pipe) == -1)
			ft_error(input);
		//ft_init_struct(input, argv, envp);
		input->first_fd = open(argv[1], O_RDONLY);
		if (input->first_fd == -1)
			ft_error(input);
		input->second_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (input->second_fd == -1)
			ft_error(input);
		input->env = envp;
		ft_child1_process(input, argv);
		ft_child2_process(input, argv);
		close(input->fd_pipe[0]);
		close(input->fd_pipe[1]);
		waitpid(-1, &input->first_fd, 0);
		waitpid(-1, &input->second_fd, 0);
		ft_close_fds(input);
		free(input);
		return (0);
	}
}
