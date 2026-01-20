/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:34:12 by acollon           #+#    #+#             */
/*   Updated: 2026/01/20 01:54:26 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parser_token_value(const t_tokens *token)
{
	if (!token || !token->token)
		return (NULL);
	return (ft_strdup(token->token));
}
