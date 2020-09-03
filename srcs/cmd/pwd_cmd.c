/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:29:18 by adbenoit          #+#    #+#             */
/*   Updated: 2020/09/03 22:52:52 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_pwd(t_stock **cmd_lst, char *envp[])
{
    (void)envp;
    (*cmd_lst)->ret = 0;
}