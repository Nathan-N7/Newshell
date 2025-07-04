/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:55:30 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 15:54:44 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

/*void	print_commands(t_command *cmds)
{
	int	i;
	int	j;

	i = 1;
	while (cmds)
	{
		j = 0;
		printf("-- Command %d:\n", i++);
		while (cmds->args && cmds->args[j])
		{
			printf("    Arg[%d]: %s\n", j, cmds->args[j]);
			j++;
		}
		j = 0;
		while (j < cmds->redirect_count)
		{
			const char *redir_type[] = { "WORD", "PIPE", "<", ">", ">>", "<<" };
			printf("-> Redirect: type=%s, file=%s\n",
				redir_type[cmds->redirects[j].type],
				cmds->redirects[j].filename);
			j++;
		}
		cmds = cmds->next;
	}
}

void	print_tokens(t_token *tokens)
{
	t_token *tmp = tokens;
    while (tmp)
    {
        printf("TOKEN: type=%d, value=%s\n", tmp->type, tmp->value);
        tmp = tmp->next;
    }
}*/

t_command	*new_command(t_token *tok, t_command **head)
{	
	int			arg_count;
	int			redir_count;
	t_command	*new;

	count_args_redirs(tok, &arg_count, &redir_count);
	new = ft_calloc(1, sizeof(t_command));
	if (!new)
		return (NULL);
	new->args = ft_calloc(arg_count + 1, sizeof(char *));
	if (!new->args)
		return (free(new), NULL);
	if (redir_count > 0)
	{
		new->redirects = ft_calloc(redir_count, sizeof(t_redirect));
		if (!new->redirects)
		{
			free(new->args);
			free(new);
			return (NULL);
		}
	}
	if (!*head)
		*head = new;
	return (new);
}

int	parse_token2(t_command **cmd, t_token **tok, int *c, t_envp *env)
{
	if ((*tok)->type == WORD)
		handle_word(*cmd, *tok, c, env);
	else if ((*tok)->type == REDIR_IN || (*tok)->type == REDIR_OUT
		|| (*tok)->type == APPEND || (*tok)->type == HEREDOC)
	{
		if (!handle_redir(*cmd, tok))
			return (0);
	}
	else if ((*tok)->type == PIPE)
	{
		if (!handle_pipe(cmd, tok, c))
			return (0);
	}
	return (1);
}

t_command	*parse_tokens(t_token *tokens, t_envp *env)
{
	t_command	*head;
	t_command	*current;
	t_token		*tok;
	int			count;

	head = NULL;
	current = NULL;
	tok = tokens;
	count = 0;
	while (tok)
	{
		if (!current)
		{
			current = new_command(tok, &head);
			if (!current)
				return (free_commands(head), NULL);
		}
		if (!parse_token2(&current, &tok, &count, env))
			return (free_commands(head), NULL);
		tok = tok->next;
	}
	return (current->args[count] = NULL, head);
}

t_command	*parsing(char *input, t_envp *env)
{
	char		*read;
	t_token		*tokens;
	t_command	*commands;

	read = ft_strtrim(input, " \t\n\v\r\f");
	if (!read || read[0] == '\0')
		return (free(read), NULL);
	if (!verify_aspas(read))
	{
		free(read);
		my_printf_fd("\033[1;31m🚨 Syntax Error: Aspas abertas\033[0m\n", 2);
		env->last_stats = 2;
		return (NULL);
	}
	tokens = tokenize(read);
	if (syntax_analyzer(tokens, env) == -1)
	{
		free(read);
		free_tokens(tokens);
		return (NULL);
	}
	commands = parse_tokens(tokens, env);
	free(read);
	free_tokens(tokens);
	return (commands);
}
