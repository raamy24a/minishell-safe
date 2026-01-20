/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 00:20:02 by radib             #+#    #+#             */
/*   Updated: 2026/01/20 02:15:07 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	stripped_length(const char *token)
{
	size_t	i;
	size_t	len;
	char	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (token[i])
	{
		if (token[i] == 39 || token[i] == '"')
		{
			quote = token[i++];
			while (token[i] && token[i++] != quote)
				len++;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

static char	*strip_quotes(const char *token)
{
	char	*result;
	size_t	i;
	size_t	j;
	char	quote;

	result = (char *)ft_calloc(stripped_length(token) + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (token[i])
	{
		if (token[i] == 39 || token[i] == '"')
		{
			quote = token[i++];
			while (token[i] && token[i] != quote)
				result[j++] = token[i++];
			if (token[i] == quote)
				i++;
		}
		else
			result[j++] = token[i++];
	}
	return (result);
}

void	expand_commands(t_command *cmds, t_env *env, int last_status)
{
	
}
