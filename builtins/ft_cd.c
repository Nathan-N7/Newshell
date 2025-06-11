#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

void    set_path(char **envp, char *path, char *name)
{
    int     i;
    char    *tmp;
    char    *new_var;

    i = get_index(envp, name);
    if (i == -1)
        return ;
    free(envp[i]);
    tmp = ft_strjoin(name, "=");
    new_var = ft_strconcat(tmp, path);
    envp[i] = new_var;
}

int tratative(char *path)
{
    if (access(path, F_OK) != 0)
    {
        my_printf_fd("minishell: cd: %s: No such file or directory\n", 2 ,path);
        return (1);
    }
    if (isdirectory(path) == 0)
    {
        my_printf_fd("minishell: cd: %s: Not a directory\n", 2, path);
        return (1);
    }
    if (access(path, X_OK) != 0)
    {
        my_printf_fd("minishell: cd: %s: Permission denied\n", 2, path);
        return (1);
    }
    return (0);
}

int ft_cd(char *path, t_envp *env)
{
    char    *home;
    char    *path_old;
    char    *path_pwd;

    if (!path)
    {
        home = getenv("HOME");
        if (!home)
        {
            my_printf_fd("minishell: cd: HOME not set\n", 2);
            return (1);
        }
        path = home;
    }
    if (tratative(path))
        return (1);
    path_old = getcwd(NULL, 0);
    if (chdir(path) != 0)
        return (free(path_old), perror("cd"), 1);
    path_pwd = getcwd(NULL, 0);
    set_path(env->envp, path_old, "OLDPWD");
    set_path(env->envp, path_pwd, "PWD");
    free(path_old);
    free(path_pwd);
    return (0);
}
