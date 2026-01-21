/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 00:20:02 by radib             #+#    #+#             */
/*   Updated: 2026/01/21 00:33:33 by radib            ###   ########.fr       */
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

char	**expand_dollars(char *s, int x, t_env *env)
{
	char	*temp;
	char	**return_str;

	return_str = malloc(sizeof(char *) * 3);
	while (s[x] >= '0' && (s[x] <= '9' || s[x] >= 'A')
		&& (s[x] <= 'Z' || s[x] >= 'a') && (s[x] <= 'z' || s[x] == '_'))
		x++;
	temp = malloc(sizeof(char) * (x + 1));
	if (!temp)
		exit_call(1, env);
	x = 0;
	while (s[x] >= '0' && (s[x] <= '9' || s[x] >= 'A')
		&& (s[x] <= 'Z' || s[x] >= 'a') && (s[x] <= 'z' || s[x] == '_'))
	{
		temp[x] = s[x];
		x++;
	}
	temp[x] = '\0';
	return_str[0] = get_value_of_key(env, temp);
	return_str[2] = NULL;
	return_str[1] = &s[x];
	return (free(temp), return_str);
}

int	expand_str(char *str, char **argv, int i)
{
	char	*copy;

	copy = ft_strdup(*argv);
	copy[i] = '\0';
	(*argv) = ft_strjoin(copy, str);
	free(copy);
	if (!*argv)
		return (-1);
	return (ft_strlen(str) - 1);
}
int	expand_str_two(char **str, char **argv, int i)
{
	char	*copy;
	char	*temp;

	copy = ft_strdup(*argv);
	copy[i] = '\0';
	temp = ft_strjoin(copy, str[0]);
	(*argv) = ft_strjoin(temp, str[1]);
	free(copy);
	if (!*argv)
		return (-1);
	return (ft_strlen(str[0]) - 1);
}
int	skip_single(char *argv, int i)
{
		if (argv[i] == 39)
	{
		while (argv[++i] != 39)
			;
	}
	return (i);
}

int	expand_argv(char **argv, int i, int last_status, t_env *env)
{
	int	last;
	int yes;

	yes = 1;
	while (argv[0][i])
	{
		last = i;
		if (argv[0][i] == '"')
			yes *= -1;
		if (yes == 1)
			i = skip_single(argv[0], i);
		if (argv[0][i] == '$')
		{
			if (argv[0][i + 1] && argv[0][i + 1] == '?')
				i += expand_str(ft_itoa(last_status), argv, i);
			else
				i += expand_str_two(expand_dollars(&argv[0][i + 1], 0, env), argv, i);
		}
		if (i < last)
			return (1);
		i++;
	}
	return (0);
}

void	expand_commands (t_command *cmds, t_env *env, int last_status)
{
	int	i;

	while (cmds)
	{
		i = -1;
		while (cmds->argv[++i])
		{
			expand_argv(&cmds->argv[i], 0, last_status, env);
			cmds->argv[i] = strip_quotes(cmds->argv[i]);
		}
		cmds = cmds->next;
	}
}
