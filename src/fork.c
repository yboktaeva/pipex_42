/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:06:14 by yuboktae          #+#    #+#             */
/*   Updated: 2023/05/16 15:20:29 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*command;

	i = 0;
	if (access(*paths, F_OK) == 0)
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	first_cmd(t_pipex pix, char **argv, char **envp)
{
	close(pix.pipefd[0]);
	if (dup2(pix.pipefd[1], STDOUT_FILENO) == -1)
		msg_sys(ERR_DUPOUT);
	if (dup2(pix.infile, STDIN_FILENO) == -1)
		msg_sys(ERR_DUPIN);
	pix.args_cmd = ft_split(argv[2], ' ');
	if (pix.path_cmd)
		pix.cmd = get_cmd(pix.path_cmd, pix.args_cmd[0]);
	else
		pix.cmd = pix.args_cmd[0];
	if (ft_strchr(argv[2], '/') == NULL)
		pix.cmd = ft_strjoin("/usr/bin/", pix.args_cmd[0]);
	if (pix.cmd == NULL)
		msg_sys(ERR_CMD);
	if (execve(pix.cmd, pix.args_cmd, envp) == -1)
		msg_error(ERR_EXE);
	close(pix.pipefd[1]);
	exit (0);
}

void	second_cmd(t_pipex pix, char **argv, char **envp)
{
	close(pix.pipefd[1]);
	if (dup2(pix.pipefd[0], STDIN_FILENO) == -1)
		msg_sys(ERR_DUPIN);
	if (dup2(pix.outfile, STDOUT_FILENO) == -1)
		msg_sys(ERR_DUPOUT);
	pix.args_cmd = ft_split(argv[3], ' ');
	if (pix.path_cmd)
		pix.cmd = get_cmd(pix.path_cmd, pix.args_cmd[0]);
	else
		pix.cmd = pix.args_cmd[0];
	if (ft_strchr(argv[3], '/') == NULL)
		pix.cmd = ft_strjoin("/usr/bin/", pix.args_cmd[0]);
	if (pix.cmd == NULL)
		msg_sys(ERR_CMD);
	if (execve(pix.cmd, pix.args_cmd, envp) == -1)
		msg_error(ERR_EXE);
	close(pix.pipefd[0]);
	exit (0);
}
