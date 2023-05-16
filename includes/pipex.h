/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:02:49 by yuboktae          #+#    #+#             */
/*   Updated: 2023/05/16 15:20:39 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ERR_ARG "Invalide number of arguments\n"
# define ERR_ENV "Environment does not exist\n"
# define ERR_FILE "file"
# define ERR_PIPE "pipe"
# define ERR_CMD "command not found\n"
# define ERR_FORK "fork"
# define ERR_DUPIN "Error: failed to redirect standard input\n"
# define ERR_DUPOUT "Error: failed to redirect standard output\n"
# define ERR_EXE "execve"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
	int		infile;
	int		outfile;
	char	*path;
	char	*cmd;
	char	**path_cmd;
	char	**args_cmd;
}	t_pipex;

void	msg_error(char *error);
int		msg_sys(char *error);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_free(t_pipex *pix);
void	free_parent(t_pipex *pix);
void	first_cmd(t_pipex pix, char **argv, char **envp);
void	second_cmd(t_pipex pix, char **argv, char **envp);
#endif
