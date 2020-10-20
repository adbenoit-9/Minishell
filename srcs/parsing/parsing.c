/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:10:44 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/20 19:24:25 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_error(t_stock **new, t_stock **cmd_lst)
{
	int err;

	err = (*new)->err;
	if (err >= -1)
		return (0);
	ft_stockclear(new, clear_one);
	if (err == MALL_ERR)
		write_error("", strerror(errno), "\n");
	else if (err == QUOTE_NOT_FOUND)
		write_error("quote missing", "", "\n");
	else
		return (0);
	ft_stockclear(cmd_lst, clear_one);
	return (err);
}

int		parse_str(char **str)
{
	size_t	i;
	int		quote;
	int 	s1;
	int		s2;

	i = 0;
	quote = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\')
			++i;
		quote = is_in_quote(*str, &i, quote);
		if (quote == 0 && (*str)[i] == '\t')
			(*str)[i] = ' ';
		if ((*str)[i] && quote == 0 && ft_issep((*str)[i], 0) == 1)
		{
			i += set_sep(*str, &s1);
			while ((*str)[i] == ' ')
				++i;
			if (!(*str)[i] && s1 > 1)
				return (sep_error(-1, s1));
			if ((*str)[i] && ft_issep((*str)[i], 0) == 1)
			{
				i += set_sep(*str, &s2);
				if (sep_error(s2, s1) == -1)
					return (-1);
			}
			else if (i == 1 && (s1 == COMA || s1 == PIPE))
				return (sep_error(-1, s1));
		}
		else
			++i;
	}
	return (0);
}

int		parsing(char *str, t_stock **cmd_lst, char *envp[])
{
	int			i;
	int			j;
	size_t		size;
	int			ret;
	static char	*cmd_str[NUM_CMD] = {"echo", "cd", "pwd", "env",
								"export", "unset", "exit"};

	if ((ret = parse_str(&str)) == -1)
		return (-1);
	if (ret == 1)
		return (-1);
	// printf("ret = %d\n", ret);
	j = 0;
	while (str[j] == ' ')
		++j;
	i = 0;
	while (str[j] && i < NUM_CMD)
	{
		size = ft_strlen(cmd_str[i]);
		if (ft_strncmp(cmd_str[i], str + j, size) == 0 &&
		(ft_issep(str[j + size], 0) == 1 || ft_isspace(str[j + size]) == 1
		|| str[j + size] == 0))
			return (save_cmd(str + j + size, cmd_lst, i, envp));
		i++;
	}
	if (str[j] && i == UNKNOW)
		return (save_cmd(str + j, cmd_lst, i, envp));
	return (0);
}
