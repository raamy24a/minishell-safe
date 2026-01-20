/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 00:20:02 by radib             #+#    #+#             */
/*   Updated: 2026/01/20 01:00:03 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void expand_commands(t_command *cmds, t_env *env, int last_status)
{
        t_command *cmd;
        t_redir *redir;
        size_t i;
        (void)env;

        printf("=== Shell Debug Dump ===\n");
        printf("Last exit status: %d\n", last_status);
        cmd = cmds;
        while (cmd)
        {
            printf("\nCommand:\n");
            // printf("  argc: %zu\n", cmd->argc);
            printf("  argv:\n");
            if (cmd->argv)
            {
                for (i = 0; i < cmd->argc; i++)
                    printf("    [%zu]: %s\n", i, cmd->argv[i]);
            }
            else
                printf("    (null)\n");

            printf("  pipe_before: %s, pipe_after: %s\n",
                   cmd->pipe_before ? "true" : "false",
                   cmd->pipe_after ? "true" : "false");

            printf("  redirections:\n");
            redir = cmd->redirs;
            if (!redir)
                printf("    (none)\n");
            while (redir)
            {
                printf("    type: ");
                switch (redir->type)
                {
                case REDIR_IN:
                    printf("<");
                    break;
                case REDIR_OUT:
                    printf(">");
                    break;
                case REDIR_APPEND:
                    printf(">>");
                    break;
                case REDIR_HEREDOC:
                    printf("<<");
                    break;
                }
                printf(", target: '%s', quoted: %d\n",
                       redir->target ? redir->target : "(null)",
                       redir->quoted);
                redir = redir->next;
            }

            cmd = cmd->next;
        }
        printf("=== End Debug Dump ===\n");
}
    // while (cmds)
    // {
    //   expand_argv(cmds, env, last_status);
    //   expand_redirs(cmds, env, last_status);
    //   cmds = cmds->next;
    // }
