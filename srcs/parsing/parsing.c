/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:10:44 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/06 20:29:03 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_str(char *str)
{
	size_t	i;
	int		quote;
	int 	s1;
	int		s2;
	int		tmp;

	i = 0;
	quote = 0;
	s1 = -1;
	while (str[i])
	{
		s2 = NONE;
		tmp = i;
		quote = is_in_quote(str, &i, quote);
		i = quote == 0 ? tmp : i;
		if (str[i] == '\\' && !str[i + 1])
		{
			write_error("", "syntax error : char expected after `\\'\n", "", 258);
			return (-1);
		}
		else if (str[i] == '\\')
		{
			i += 2;
			s1 = NONE;
		}
		else if (str[i] && quote == 0 && ft_issep(str[i], 0) == 1)
		{
			if (s1 == NONE)
				s1 = set_sep(str + i, &i);
			else if (s1 != NONE && str[i])
				s2 = set_sep(str + i, &i);
			if ((!str[i] && s1 != COMA)|| i == 1)
				s2 = s1;
			if (sep_error(s1, s2) == -1)
				return (-1);
		}
		else if (str[i])
		{
			if (str[i] != ' ')
				s1 = NONE;
			++i;
		}
	}
	return (0);
}

int		parsing(char *str, char *envp[])
{
	int	ret;
	int	i;
	t_stock *tmp;

	ft_stockclear(&g_cmd, clear_one);
	ret = save_cmd(str, &g_cmd, envp);
	i = 0;
	tmp = g_cmd;
	while (ret >= 0 && tmp->sep == PIPE)
	{
		i += ret;
		ret = save_cmd(str + i, &tmp->next,envp);
		tmp = tmp->next;
	}
	if (ret >= 0)
		i += ret;
	if (g_cmd->err == 0)
		execute(&g_cmd, envp);
	if(g_cmd->err != EXIT_ERROR && ret >= 0 && str[ret])
		return (parsing(str + i, envp));
	return (0);
}
