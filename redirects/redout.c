#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

void file_exists_redout(char *pathname, int *error_flag)
{
    int fd;

	if (isdirectory(pathname))
	{
		my_printf_fd("minishell: %s: Is a directory\n", 2,pathname);
		*error_flag = TRUE;
		return ;
	}
	if (access(pathname, W_OK) != 0)
	{
		my_printf_fd("minishell: %s: Permission Denied\n", 2, pathname);
		*error_flag = TRUE;
		return ;
	}
	fd = open(pathname, O_WRONLY | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void new_file_redout(char *pathname)
{
	int fd;

    fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void handle_redout(t_redirect *redir, int *error_flag, char **envp)
{
	char *fname;
	char *pathname;

    fname = redir->filename;
    pathname = create_pathname(fname, envp);
	if (!pathname)
		return ;
	if (access(pathname, F_OK) == 0)
		file_exists_redout(pathname, error_flag);
	else
		new_file_redout(pathname);
	free(pathname);
}
