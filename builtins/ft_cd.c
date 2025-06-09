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
    tmp = ft_strconstjoin(name, "=");
    new_var = ft_strjoin(tmp, path);
    envp[i] = new_var;
}

int ft_cd(char *path, t_envp *env)
{
    char    *home;
    char    *path_old;
    char    *path_pwd;
    char    *new_path;

    if (!path || ft_strncmp(path, "~", 1) == 0)
    {
        home = getenv("HOME");
        if (!home)
        {
            my_printf_fd("minishell: cd: HOME not set\n", 2);
            return (1);
        }
        if (path && ft_strcmp(path, "~") != 0)
        {
            new_path = ft_substr(home, 1, ft_strlen(path));
            new_path = ft_strjoin(home, new_path);
        }
        else
            new_path = home;
    }
    if (access(new_path, F_OK) != 0)
    {
        my_printf_fd("minishell: cd: %s: No such file or directory\n", 2 ,new_path);
        return (1);
    }
    if (isdirectory(new_path) == 0)
    {
        my_printf_fd("minishell: cd: %s: Not a directory\n", 2, new_path);
        return (1);
    }
    if (access(new_path, X_OK) != 0)
    {
        my_printf_fd("minishell: cd: %s: Permission denied\n", 2, new_path);
        return (1);
    }
    path_old = getcwd(NULL, 0);
    if (chdir(new_path) != 0)
        return (free(path_old), perror("cd"), 1);
    path_pwd = getcwd(NULL, 0);
    set_path(env->envp, path_old, "OLDPWD");
    set_path(env->envp, path_pwd, "PWD");
    return (0);
}
