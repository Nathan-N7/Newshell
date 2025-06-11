#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

void	free_redirect(t_redirect *redir)
{
	if (redir == NULL)
		return ;
	if (redir->filename != NULL)
	{
		free(redir->filename);
		redir->filename = NULL;
	}
}

void	handle_heredoc_son(t_redirect *redir, t_envp *env, int write_fd, int read_fd)
{
	char	*rline;
	char	*e_rline;

	close (read_fd);
	while (1)
	{
		rline = readline(">");
		if (!rline || !ft_strcmp(rline, redir->filename))
		{
			free(rline);
			break ;
		}
		e_rline = get_value(rline, env->envp);
		my_printf_fd("%s\n", write_fd, e_rline);
		free(rline);
		free(e_rline);
	}
	free_redirect(redir);
	free_env(env->envp);
	close(write_fd);
}

int  handle_heredoc(t_redirect *redir, t_envp *env)
{
	int	pid;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		handle_heredoc_son(redir, env, pipefd[1], pipefd[0]);
		exit (0);
	}
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	redir->fd = pipefd[0];
	return (0);
}

// void	handle_heredoc_son(t_redirect *redir, t_envp *env)
// {
// 	char    *rline;
//     int     pipefd[2];
// 	char	*e_rline;

// 	pipe(pipefd);
// 	while (1)
// 	{
// 		rline = readline(">");
// 		if (!rline)
// 			break ;
// 		if (!ft_strcmp(rline, redir->filename))
// 		{
// 			free(rline);
// 			break ;
// 		}
// 		e_rline = expand_var(rline, env);
// 		my_printf_fd("%s\n", pipefd[1], e_rline);
// 		free(rline);
// 		free(e_rline);
// 	}
// 	close(pipefd[1]);
// 	dup2(pipefd[0], STDIN_FILENO);
// 	close(pipefd[0]);
// }

