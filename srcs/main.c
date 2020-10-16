/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:05 by mabriand          #+#    #+#             */
/*   Updated: 2020/10/16 14:02:29 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stocknclear(t_stock **cmd_lst, int n)
{
	while (n > 0)
	{
		*cmd_lst = (*cmd_lst)->next;
		--n;
	}
	if ((*cmd_lst)->next && ((*cmd_lst)->next->sep == LEFT || (*cmd_lst)->next->sep == RIGHT || (*cmd_lst)->next->sep == D_RIGHT))
		stocknclear(&(*cmd_lst)->next, 0);
	clear_one(cmd_lst);
	// EUUUUH NON. On va plutot faire un tableau de stdin et stdout dans le debut du parsing, merci comme ca byre redirection !!!!!!
}

int main(int argc, char *argv[], char *envp[])
{
	char shell[] = {0xF0, 0x9F, 0x90, 0x9A, ':', ' '};
	char *buffer;
	t_stock	*cmd_lst;
	t_stock	*tmp;
	int	ret;
	int i;

	(void)argc;
	(void)argv;
	while (1)
	{
		write(1, "\033[1mLesPetitsCoquillages\033[0m", 29);
		write(1, shell, 6);
		// ret = read(0, buffer, 4098);
		// buffer[ret] = 0;
		buffer = NULL;
		ret = get_next_line(0, &buffer);
		cmd_lst = NULL;
		parsing(buffer, &cmd_lst, envp);
		// tmp = cmd_lst;
		// while (tmp)
		// {
		// 	i = -1;
		// 	while (tmp->input && tmp->input[++i])
		// 		printf("[%s]\n", tmp->input[i]);
		// 	tmp = tmp->next;
		// 	printf("---------------\n");
		// }
		i = 0;
		ret = last_parsing(&cmd_lst, &i);
		tmp = cmd_lst;
		if (ret == -2)
		{
			stocknclear(&cmd_lst, i);
			ret = 0;
		}
		if (ret == 0)
			execute(&cmd_lst, envp);
		ft_stockclear(&cmd_lst, clear_one);
		free(buffer);
		buffer = NULL;
	}
	return (0);
}
