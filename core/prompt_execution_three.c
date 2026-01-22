/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_execution_three.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:35:30 by radib             #+#    #+#             */
/*   Updated: 2026/01/22 16:57:08 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin_child(char *builtin_str)
{
	if (ft_strcmp(builtin_str, "echo") == 0)
		return (1);
	else if (ft_strcmp(builtin_str, "pwd") == 0)
		return (2);
	else if (ft_strcmp(builtin_str, "env") == 0)
		return (7);
	return (0);
}

void	child_execute_suite(t_command *cmd,
		int input_fd, int output_fd, t_env *env)
{
	if (apply_redirections(cmd->redirs, &input_fd, &output_fd) == -1)
		exit_call(EXIT_FAILURE, env);
	if (dup2(input_fd, STDIN_FILENO) == -1)
		perror("dup2");
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		perror("dup2");
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (output_fd != STDOUT_FILENO)
		close(output_fd);
}

void	child_execute(t_f **tc, int prev_fd, int next_fd, t_env *env)
{
	int		input_fd;
	int		output_fd;
	char	**str_env;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	input_fd = prev_fd;
	output_fd = next_fd;
	if (input_fd == -1)
		input_fd = STDIN_FILENO;
	if (output_fd == -1)
		output_fd = STDOUT_FILENO;
	child_execute_suite((*tc)->cmds, input_fd, output_fd, env);
	if (prev_fd != -1 && prev_fd != input_fd)
		close(prev_fd);
	if (next_fd != -1 && next_fd != output_fd)
		close(next_fd);
	if (is_builtin_child((*tc)->cmds->argv[0]))
		exit_call_silent(exec_builtin(is_builtin_child((*tc)->cmds->argv[0]),
				(*tc)->cmds->argv, env), env);
	str_env = env_to_char_array(env, 0);
	px_exec((*tc)->cmds->argv, str_env, tc);
	free_split(str_env);
	exit_call(127, env);
}

int	execute_commands_suite(pid_t last_pid
		, t_f **tc, t_env *env, int pipefd[2])
{
	int		prev_fd;

	prev_fd = -1;
	last_pid = -1;
	last_pid = launch_command(tc, prev_fd, pipefd[1], env);
	if (last_pid < 0)
		return (1);
	if (prev_fd != -1)
		close(prev_fd);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	prev_fd = pipefd[0];
	(*tc)->cmds = (*tc)->cmds->next;
	return (0);
}

int	execute_commands(t_command *cmd, t_env *env, int count, t_f **tc)
{
	pid_t	last_pid;
	int		pipefd[2];

	last_pid = -1;
	while (cmd)
	{
		if (cmd->pipe_after)
		{
			if (pipe(pipefd) == -1)
				return (perror("pipe"), 1);
		}
		else
		{
			pipefd[0] = -1;
			pipefd[1] = -1;
		}
		if (execute_commands_suite(last_pid, tc, env, pipefd))
			return (1);
		cmd = cmd->next;
		count++;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (wait_children(last_pid, count + 1));
}
