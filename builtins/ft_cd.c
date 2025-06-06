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
    new_var = ft_strjoin(tmp, path);
    free (tmp);
    envp[i] = new_var;
}

int ft_cd(char *path, t_envp *env)
{
    char    *home;
    char    *path_old;
    char    *path_pwd;

    (void)env;
    path_old = getcwd(NULL, 0);
    if (!path || ft_strcmp(path, "~") == 0)
    {
        home = getenv("HOME");
        if (!home)
            return (printf("cd: HOME not set\n"), 1);
        path = home;
    }
    if (chdir(path) != 0)
        return (free(path_old), perror("cd"), 1);
    path_pwd = getcwd(NULL, 0);
    set_path(env->envp, path_old, "OLDPWD");
    set_path(env->envp, path_pwd, "PWD");
    return (free(path_old), free(path_pwd), 0);
}