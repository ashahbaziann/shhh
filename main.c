/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:32:14 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/09/23 14:16:03 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	print_commands(t_shell *shell)
{
	t_commands	*current;
	char		**arg;
	int			i;

	i = 0;
	arg = shell->command->args;
	current = shell->command;
	while (current)
	{
		printf("Command: %s \n", current->name);
		if (arg)
		{
			i = 0;
			while (arg[i])
			{
				//	printf("hhhhhhhhh\n");
				printf("index: %d , Args:%s\n", i, arg[i]);
				i++;
			}
		}
		current = current->next;
	}
}

void	print_tokens(t_shell *shell)
{
	t_token	*current;

	current = shell->token;
	while (current)
	{
		printf("Token: %s | Type: %d | State: | %d Variable: | %s\n",
			current->value, current->type, current->state, current->var_value);
		current = current->next;
	}
}

void	print_env(t_shell *shell)
{
	env_list	*current;

	current = shell->env;
	while (current)
	{
		printf("%s%s\n", current->key, current->value);
		current = current->next;
	}
}

void	print_exp(t_shell *shell)
{
	env_list	*current;

	current = shell->exp;
	while (current)
	{
		printf("declare -x %s\"%s\"\n", current->key, current->value);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell);
	while (1)
	{
		shell.input = readline("./minishell ");
		//system("leaks minishell");
		if (!shell.input)
			error(READLINE_ERR, &shell);
		if (shell.input[0] != '\0')
			add_history(shell.input);
		get_environment(&shell, env);
		lexical_analyzer(&shell);
		//create_commands(&shell);
		print_tokens(&shell);
		//print_commands(&shell);
		free_shell(&shell);
		system("leaks minishell");
	}
	free_env(shell.env);
	shell.env = NULL;
	free_shell(&shell);
	//system("leaks minishell");
	return (0);
}
