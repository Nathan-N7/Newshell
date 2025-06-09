#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

void	sigint_heredoc(int	sig)
{
	(void)sig;
	write(2, "\n", 1);
	exit(130);
}

void	handle_heredoc_son(t_redirect *redir, t_envp *env, int write_fd)
{
	char	*rline;
	char	*e_rline;

	while (1)
	{
		rline = readline(">");
		if (!rline || !ft_strcmp(rline, redir->filename))
		{
			free(rline);
			break;
		}
		e_rline = expand_var(rline, env);
		my_printf_fd("%s\n", write_fd, e_rline);
		free(rline);
		free(e_rline);
	}
}

int	handle_heredoc(t_redirect *redir, t_envp *env)
{
	int	pipefd[2];
	int	pid;
	int	status;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, sigint_heredoc);
		close(pipefd[0]);
		handle_heredoc_son(redir, env, pipefd[1]);
		close(pipefd[1]);
		exit(0);
	}
	close(pipefd[1]);
	redir->fd = pipefd[0];
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		env->last_stats = 130;
		return (-1);
	}
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

