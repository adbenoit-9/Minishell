/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:29:07 by adbenoit          #+#    #+#             */
/*   Updated: 2020/10/19 13:42:23 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int     ft_check_var(char *var)
// {
//     int i;

//     i = 0;
//     while (var[i] != '\0')
//     {
//         if (ft_isalnum(var[i++]) == 0)
//             return (0);
//     }
//     return (1);
// }

// char    *ft_create_var(char *str, int *pos)
// {
//     char    *var;
//     int     i;

//     var = NULL;
//     i = 0;
//     while(str[i] && str[i] != '=')
//         i++;
//     if(!(var = (char *)malloc(sizeof(char) * i + 1)))
//         return (NULL);
//     i = 0;
//     while(str[i] && str[i] != '=')
//     {
//         var[i] = str[i];
//         i++;
//     }
//     var[i] = '\0';
//     if (ft_check_var(var) == 0)
//     {
//         write_error("export: \'", str, "\': not a valid identifier\n");
//         return(NULL);
//     }
//     if (str[i] != '=')
//         return (NULL);
//     *pos = i;
//     return (var);
// }

// void    ft_add_to_envp(char *envp[], char *str)
// {
//     int i;
//     int j;

//     i = 0;
//     j = 0;
//     while(envp[i] != 0)
//         i++;
//     if (!(envp[i] = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)))
//         return ;
//     while (str[j] != 0)
//     {
//         envp[i][j] = str[j];
//         j++;
//     }
//     envp[i][j] = 0;
//     envp[i + 1] = 0;
// } // lignes ajoutées à free quand on quitte le pgm :
// //peut être avoir quelque part la taille initiale de envp ???

// void    ft_resize_at_pos(char *envp[], char *var, char *new, int pos)
// {
//     int size;
//     int i;
//     int j;

//     size = ft_strlen(var) + ft_strlen(new) + 1;
//     envp[pos] = ft_realloc(envp[pos], size); // a free
//     i = 0;
//     j = 0;
//     while (var[i] != '\0')
//         envp[pos][j++] = var[i++];
//     envp[pos][j++] = '=';
//     i = 0;
//     while (new[i] != '\0')
//         envp[pos][j++] = new[i++];
//     envp[pos][j++] = '\0';
// }


// void    ft_modify_envp(char *envp[], char *var, char *new, int pos)
// {
//     int i;
//     int j;
//     int k;
//     int l;

//     i = ft_strlen(var) + 1;
//     j = ft_strlen(new);
//     k = 0;
//     l = i;
//     while (envp[pos][l] != '\0')
//         l++;
//     if (l - i == j)
//     {
//         while (j >= i)
//             envp[pos][i++] = new[k++];
//         envp[pos][i] = '\0';
//     }
//     else
//         ft_resize_at_pos(envp, var, new, pos);
// }


void    ft_export(t_stock **cmd_lst, char *envp[])
{
    // int     pos;
    // int     ret;
    // char    *var;
    // char    *new;

    // if (ft_redirect(cmd_lst, 0, 0) == -1)
    //     return ;
    // if (!(var = ft_create_var((*cmd_lst)->tokens[0], &pos)))
    //     return ;
    // ret = find_var(envp, var);
    // new = ft_strdup((*cmd_lst)->tokens + pos);
    // if (ret == -1)
    //     ft_add_to_envp(envp, (*cmd_lst)->tokens);
    // else
    //     ft_modify_envp(envp, var, new, ret);
    (void)envp;
    (*cmd_lst)->ret = 0;
}