/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:16:21 by adbenoit          #+#    #+#             */
/*   Updated: 2020/11/03 16:19:17 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_file(char **file, char *str, t_stock **cmd_lst, char **envp)
{
	size_t	i;
	int		j;
	int		len;

	i = 1;
	while (str[i] == ' ')
		++i;
	if (*file)
		free(*file);
	if ((len = ft_strlen(str + i)) == 0)
		return (SEP_ERR);
	if (!(*file = malloc(len + 1)))
		return (MALL_ERR);
	j = -1;
	--i;
	while (str[++i])
		(*file)[++j] = str[i];
	(*file)[j + 1] = 0;
	parse_token(*file, file, cmd_lst, envp);
	return (i);
}

int			set_file_name(t_stock **cmd_lst, char *str, char **envp)
{
	int i;
	int fd;

	i = 0;
	if (str[i] == '<' && str[++i])
	{
		i = parse_file(&(*cmd_lst)->input, str, cmd_lst, envp);
		errno = 0;
		fd = open((*cmd_lst)->input, O_RDONLY);
		if (i > 0 && fd == -1)
		{
			write_error((*cmd_lst)->input, ": ", strerror(errno), 1);
			write(1, "\n", 1);
			close(fd);
			return (FILE_ERR);
		}
		close(fd);
	}
	else if (str[i])
	{
		i = parse_file(&(*cmd_lst)->output, str, cmd_lst, envp);
		errno = 0;
		fd = open((*cmd_lst)->output, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR |
		S_IRGRP | S_IWGRP | S_IWUSR);
		if (fd == -1 && (*cmd_lst)->output)
		{
			write_error((*cmd_lst)->output, ": ", strerror(errno), 1);
			write(1, "\n", 1);
			close(fd);
			return (FILE_ERR);
		}
		close(fd);
	}
	return (-1);
}

int			parse_token(char *token, char **new, t_stock **cmd_lst, char **envp)
{
	int		j;
	int		k;
	int		ret;

	k = 0;
	if (!(*new = malloc(ft_strlen(token) + 1)))
		return (MALL_ERR);
	j = 0;
	while (token[j])
	{
		ret = 0;
		if (token[j] == '\\' && token[++j])
			(*new)[k++] = token[j++];
		else if (token[j] == '\'')
			ret = deal_simple_quote(token + j, new, &k, 0);
		else if (token[j] == '\"')
			ret = deal_double_quote(token + j, new, &k, envp);
		else if (token[j] == '$' && token[j + 1] == '?')
			ret = deal_erret(new, &k, ft_strlen(token));
		else if (token[j] == '$')
			ret = deal_dollar(token + j, new, &k, envp);
		else if (token[j] == '>' || token[j] == '<')
			return (set_file_name(cmd_lst, token + j, envp));
		else
			(*new)[k++] = token[j++];
		if (ret < -1)
		{
			(*new)[k] = 0;
			return (ret);
		}
		else if (ret == VAR_NOT_FOUND)
		{
			free(*new);
			(*new) = 0;
			return (VAR_NOT_FOUND);
		}
		else
			j += ret;
	}
	(*new)[k] = 0;
	return (0);
}

int			set_token(char **tokens, t_stock **cmd_lst, char **envp)
{
	int	i;
	int	ret;
	int k;

	i = 0;
	k = 0;
	if (!tokens)
		return (0);
	while (tokens[i])
	{
		if ((ret = parse_token(tokens[i], &(*cmd_lst)->tokens[k],
		cmd_lst, envp)) < -1)
		{
			ft_free(tokens);
			(*cmd_lst)->tokens[++k] = NULL;
			return (ret);
		}
		if (ret != -1)
			++k;
		free(tokens[i]);
		tokens[i] = NULL;
		++i;
	}
	free(tokens);
	tokens = NULL;
	(*cmd_lst)->tokens[k] = NULL;
	return (0);
}
