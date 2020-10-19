/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:28:54 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/19 13:42:20 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo_n(t_stock **cmd_lst, int *i)
{
	int	n;
	int j;

	n = 0;
	if (!(*cmd_lst)->tokens[0])
		return (0);
	while (ft_strncmp((*cmd_lst)->tokens[*i], "-n", 2) == 0)
	{
		j = 2;
		while ((*cmd_lst)->tokens[*i][j] == 'n')
			++j;
		if ((*cmd_lst)->tokens[*i][j])
			return (n);
		++n;
		++(*i);
	}
	return (n);
}

void	ft_echo(t_stock **cmd_lst, char *envp[])
{
	int	i;
	int k;
	int	fd;
	int n;

	(void)envp;
	i = 0;
	fd = 1;
	if (!(*cmd_lst)->tokens || ft_redirect(cmd_lst, &fd, 0) == -1)
		return ;
	n = ft_echo_n(cmd_lst, &i);
	k = i - 1;
	while ((*cmd_lst)->tokens[++k])
	{
		if (k != i && (*cmd_lst)->tokens[k][0] && (*cmd_lst)->err != VAR_NOT_FOUND)
			write(1, " ", 1);
		write(fd, (*cmd_lst)->tokens[k], ft_strlen((*cmd_lst)->tokens[k]));
	}
	if (n == 0)
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
	(*cmd_lst)->ret = 0;
}
