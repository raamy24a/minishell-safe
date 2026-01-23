/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:36:10 by radib             #+#    #+#             */
/*   Updated: 2026/01/23 03:44:05 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

char	*get_pwd(void)
{
	char	*buffer;

	buffer = malloc (sizeof(char) * 4096 + 1);
	buffer[4096] = '\0';
	if (getcwd(buffer, 4096) != NULL)
	{
		return (buffer);
	}
	free(buffer);
	perror("rien pour l'instant");
	return (NULL);
}

int	call_pwd(t_f **tc)
{
	char	buffer[4096 + 1];

	buffer[4096] = '\0';
	if (getcwd(buffer, 4096) != NULL)
	{
		printf("%s\n", buffer);
		free_tc(tc);
		return (0);
	}
	free_tc(tc);
	return (errno);
}
