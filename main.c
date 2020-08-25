/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:05 by mabriand          #+#    #+#             */
/*   Updated: 2020/08/26 01:56:17 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char shell[] = {0xF0, 0x9F, 0x90, 0x9A, ':', ' '};
	char buffer[4098];
	t_list	*order;
	int	ret;

	write(1, "\033[1mLesPetitsCoquillages", 27);
	write(1, shell, 6);
	// write(1, ": ", 2);
	ret = read(0, buffer, 4098);
	buffer[ret] = 0;
	order = NULL;
	parsing(buffer, &order);
	while (order)
	{
		printf("output = %s\n", order->output);
		order = order->next;
	}
}
