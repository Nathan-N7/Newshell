#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

int get_index(char **envp, char *key)
{
    int i;
    int len;

    len = 0;
    while (key[len] && key[len] != '=')
        len++;
    i = -1;
    while (envp[++i])
        if(ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
            return (i);
    return (-1);
}

char    **removed_var(char  **envp, char *var)
{
    int i;
    int j;
    int idx;
    char    **new_env;

    i = -1;
    j = 0;
    idx = get_index(envp, var);
    if (idx == -1)
        return (envp);
    while (envp[++i])
        ;
    new_env = malloc(sizeof(char *) * i);
    if (!new_env)
        return (NULL);
    i = -1;
    while (envp[++i])
    {
        if (i == idx)
        {
            free(envp[i]);
            continue ;
        }
        new_env[j++] = envp[i];
    }
    new_env[j] = NULL;
    free(envp);
    return (new_env);
}

int verify_var_unset(char *str)
{
    int i;

    if (!str || !str[0])
        return (0);
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (0);
    i = 1;
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int ft_unset(char **args, t_envp *env)
{
    int i;

    i = -1;
    while (args[++i])
        env->envp = removed_var(env->envp, args[i]);
    if (!env->envp)
        return (1);
    return (0);
}

