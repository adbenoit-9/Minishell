/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 00:53:45 by adbenoit          #+#    #+#             */
/*   Updated: 2020/12/21 17:34:54 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_son(t_cmd *cmd, int *fd, int *p, char *envp[])
{
	g_shell.pid = 1;
	g_shell.bool = 0;
	dup2(fd[0], 0);
	if (cmd->next)
		dup2(p[1], 1);
	close(p[0]);
	run_cmd(cmd, envp, fd, 0);
	exit(EXIT_SUCCESS);
}

static void	ft_putstatus(int status)
{ 
	g_status = WEXITSTATUS(status);
	if (g_shell.sig == 1)
	{
		if (WIFSIGNALED(status) == 1)
			g_status = 130;
		else
			g_status = 255;
	}
	else if (status % 255 != 0)
		g_status = status % 255;
	else if (status != 0)
		g_status = 255;
	
}

static void	ft_mana_sig(t_cmd *cmd)
{
	if (cmd->tokens[0] && ft_strcmp(cmd->tokens[0], "make") == 0)
		g_shell.bool = 1;
	if (cmd->tokens[0] && ft_strcmp(cmd->tokens[0], "exit") == 0)
	{
		g_shell.bool = 0;
		g_shell.pid = 1;
	}
	g_shell.sig = 0;
	signal(SIGINT, proc_sig_handler);
	signal(SIGQUIT, proc_sig_handler);
	g_shell.pid = 0;
}

void		ft_fork_handle(t_cmd *cmd, char *envp[])
{
	int		p[2];
	int		fd[2];
	int		status;
	int		nb_wait;
	pid_t	pid;

	status = 0;
	nb_wait = 0;
	fd[0] = 1;
	fd[1] = 1;
	while (cmd)
	{
		ft_mana_sig(cmd);
		if (pipe(p) == -1)
			exit(errno_msg(NULL, NULL, EXIT_FAILURE));
		if ((pid = fork()) == -1)
			exit(errno_msg(NULL, NULL, EXIT_FAILURE));
		if (pid == 0)
			ft_son(cmd, fd, p, envp);
		else
		{
			run_cmd(cmd, envp, fd, 1);
			close(p[1]);
			fd[0] = p[0];
			if (cmd->next != NULL)
				cmd = cmd->next;
			else
				break ;
			nb_wait++;
		}
	}
	while (nb_wait-- >= 0)
		wait(&status);
	ft_putstatus(status);
}
