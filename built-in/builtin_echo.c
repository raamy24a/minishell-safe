/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 03:04:19 by radib             #+#    #+#             */
/*   Updated: 2026/01/23 03:43:07 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_struct.h"
#include "../libft/libft.h"

//newline = 1
//x = -1

int	echo_write(char **string, int x, int i)
{
	while (string[++x])
	{
		i = 0;
		while (string[x][i])
			write(1, &string[x][i++], 1);
		if (string[x + 1])
			write(1, " ", 1);
	}
	return (i);
}

int	echobuiltin(char **string, int newline, int x, t_f **tc)
{
	int	i;
	int	j;

	j = 0;
	while (string[j][0] == '-')
	{
		i = 1;
		while (string[j][i] && string[j][i] == 'n')
			i++;
		if (!string[j][i])
			newline = 0;
		else
			break ;
		j++;
	}
	echo_write(&string[j - 1], x, 0);
	if (newline == 1)
		printf("\n");
	free_tc(tc);
	return (0);
}
