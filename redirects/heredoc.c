#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

void	handle_heredoc_son(t_redirect *redir, t_envp *env)
{
	char	*rline;
	char	*e_rline;
	int		pipefd[2];

	pipe(pipefd);
	while (1)
	{
		rline = readline(">");
		if (!rline || !ft_strcmp(rline, redir->filename))
		{
			free(rline);
			break ;
		}
		e_rline = expand_var(rline, env);
		my_printf_fd("%s\n", pipefd[1], e_rline);
		free(rline);
		free(e_rline);
	}
	close(pipefd[1]);
	redir->fd = pipefd[0];
}

void handle_heredoc(t_redirect *redir, t_envp *env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		handle_heredoc_son(redir, env);
	}
	else
		waitpid(pid, NULL, 0);
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

