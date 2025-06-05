#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

int is_numeric(char *str)
{
    int i;

    i = 0;
    if (!str || *str == '\0')
        return (0);
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i])
    {
        if (!ft_isdigit((unsigned char)str[i]))
            return (0);
        i++;
    }
    return (1);
}

void ft_exit(char **args, t_envp *env)
{
	write(1, "exit\n", 5);
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			my_printf_fd("minishell: exit: %s: numeric argument required\n", 2, args[1]);
			env->last_stats = 2;
			exit(2);
		}
		else if (args[2])
		{
			my_printf_fd("minishell: exit: too many arguments\n", 2);
			env->last_stats = 1;
			return ;
		}
		env->last_stats = (unsigned char)ft_atoi(args[1]);
		exit(env->last_stats);
	}
	env->last_stats = 0;
	exit(0);
}