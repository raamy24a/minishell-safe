/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:31:28 by acollon           #+#    #+#             */
/*   Updated: 2026/01/22 15:00:00 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*init_shell(char **envp)
{
	t_env	*env;
	char	*nbr;

	env = init_env(envp, 0);
	if (!env)
		ft_putendl_fd("minishell: failed to initialize environment",
			STDERR_FILENO);
	nbr = ft_itoa (ft_atoi (get_value_of_key(env, "SHLVL"), 1, 0, 0) + 1);
	change_value_of_key(env, "SHLVL", nbr);
	free(nbr);
	return (env);
}
