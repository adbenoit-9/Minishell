#include "minishell.h"

int    ft_error(t_stock *cmd_lst)
{
    free(cmd_lst);
    return (0);
}

char    *output_error(char *cmd, char *arg, char *err)
{
    char    *output;

    cmd = ft_strjoin(cmd, arg);
    output = ft_strjoin(cmd, err);
    free(cmd);
    return (output);
}