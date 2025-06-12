#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

int    ft_pwd(t_envp *env)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if (!pwd)
        pwd = expand_var("$PWD", env);
    if (!pwd)
        return (1);
    printf("%s\n", pwd);
    free(pwd);
    return (0);
}