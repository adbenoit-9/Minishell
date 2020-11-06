/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:12:03 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/06 19:24:35 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_bs(char *str, size_t *i)
{
	size_t	n;

	n = 0;
	while (str[n + *i] == '\\')
		++n;
	(*i) += n;
	if ((n % 2) == 0)
		return (0);
	return (1);
}

static int	is_error(t_stock **g_cmd)
{
	int err;

	err = (*g_cmd)->err;
	if (err >= -1)
		return (0);
	if (err == MALL_ERR)
		write_error("", strerror(errno), "\n", 1);
	else if (err == QUOTE_NOT_FOUND)
		write_error("", "syntax error : quote expected\n", "", 258);
	else
		return (0);
	return (err);
}

int			save_cmd(char *str, t_stock **g_cmd, char *envp[])
{
	size_t	i;
	size_t	tmp;
	int		ret;
	char	**tokens;

	ret = 0;
	i = -1;
	while (str[++i])
	{
		tmp = i;
		ret = is_in_quote(str, &tmp, ret);
		i = ret != 0 ? tmp : i;
		if (ret == 0 && is_bs(str, &i) == 0 && (str[i] == ';' || str[i] == '|'))
			break ;
	}
	if (!(tokens = split_token(str, ' ', i)))
		return (MALL_ERR);
	*g_cmd = ft_stocknew(set_sep(str + i, &i));
	(*g_cmd)->err = set_token(tokens, g_cmd, envp);
	if ((ret = is_error(g_cmd)) == 0)
		return (i);
	return (ret);
}
