#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

int verify_arg(char *arg)
{
    int i;

    i = 1;
    if (!arg || arg[0] != '-')
        return (0);
    if (arg[1] == '\0')
        return (0);
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int ft_echo(char **arg)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    while (arg[i] && verify_arg(arg[i]))
    {
        newline = 0;
        i++;
    }
    while (arg[i])
    {
        printf("%s", arg[i]);
        if (arg[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
    return (0);
}
