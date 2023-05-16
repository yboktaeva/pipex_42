/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:00:37 by yuboktae          #+#    #+#             */
/*   Updated: 2023/05/11 10:36:58 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	msg_sys(char *error)
{
	write (2, error, ft_strlen(error));
	return (1);
}

void	msg_error(char *error)
{
	perror (error);
	exit (1);
}
