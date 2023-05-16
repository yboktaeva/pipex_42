/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:32:45 by yuboktae          #+#    #+#             */
/*   Updated: 2023/05/16 15:22:12 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_path(char **envp)
{
	if (!envp || !(*envp))
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

static void	pipex(t_pipex pix, char **argv, char **envp)
{
	if (pipe(pix.pipefd) == -1)
		msg_error(ERR_PIPE);
	pix.path = get_path(envp);
	pix.path_cmd = ft_split(pix.path, ':');
	pix.pid1 = fork();
	if (pix.pid1 < 0)
		msg_error(ERR_FORK);
	else if (pix.pid1 == 0)
	{
		first_cmd(pix, argv, envp);
		ft_free(&pix);
	}
	close(pix.pipefd[1]);
	pix.pid2 = fork();
	if (pix.pid2 < 0)
		msg_error(ERR_FORK);
	else if (pix.pid2 == 0)
	{
		second_cmd(pix, argv, envp);
		ft_free(&pix);
	}
	close(pix.pipefd[0]);
	free_parent(&pix);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pix;
	pid_t	pid;
	int		wstatus;

	if (argc != 5)
		return (msg_sys(ERR_ARG));
	pix.infile = open(argv[1], O_RDONLY, 00644);
	pix.outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (pix.infile < 0 || pix.outfile < 0)
		msg_error(ERR_FILE);
	pipex(pix, argv, envp);
	pid = waitpid(-1, &wstatus, 0);
	while (pid > 0)
		pid = waitpid(-1, &wstatus, 0);
	return (0);
}
