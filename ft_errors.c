/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbatoro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:39:40 by jbatoro           #+#    #+#             */
/*   Updated: 2022/03/29 16:43:22 by jbatoro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

/* Input error*/
void	ft_input_error(t_pipex *input)
{
	write(2, "Error Input\n./pipex [file1][cmd1][cmd2][file2]", 47);
	free(input);
	exit(EXIT_FAILURE);
}

/*Error with fd */
void	ft_fd_error(t_pipex *input)
{
	perror("error fd");
	free(input);
	exit(EXIT_FAILURE);
}

/* Cmd not found error */
void	ft_cmd_error(char **cmd, t_pipex *input)
{
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": Command Not Found\n", 20);
	if (ft_strnstr(*cmd, "/", ft_strlen(*cmd)))
	{
		free(input);
		exit(EXIT_FAILURE);
	}
	ft_free(cmd);
	free(input);
	exit(EXIT_FAILURE);
}
