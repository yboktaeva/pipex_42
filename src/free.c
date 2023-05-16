/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:55:37 by yuboktae          #+#    #+#             */
/*   Updated: 2023/05/15 11:23:04 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free(t_pipex *pix)
{
	int	i;

	i = -1;
	if (pix->args_cmd)
	{
		while (pix->args_cmd[++i])
			free(pix->args_cmd[i]);
	}
	free(pix->args_cmd);
}

void	free_parent(t_pipex *pix)
{
	int	i;

	i = -1;
	close(pix->infile);
	close(pix->outfile);
	if (pix->path_cmd)
	{
		while (pix->path_cmd[++i])
			free(pix->path_cmd[i]);
	}
	free(pix->path_cmd);
}
