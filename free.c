/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:54:50 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/09/23 13:06:47 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"



void	free_env(env_list *env)
{
	env_list	*tmp;

	if (env)
	{
		tmp = env;
		while (tmp)
		{
			tmp = tmp -> next;
			if (env -> value)
				free(env -> value);
			if (env -> key)
				free(env -> key);
			free(env);
			env = NULL;
			env = tmp;
		}
		free(env);
		env = NULL;
	}
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	if (token)
	{
		tmp = token;
		while (tmp)
		{
			tmp = tmp -> next;
			if (token -> value)
				free(token -> value);
			if (token -> var_value)
				free(token -> var_value);
			free(token);
			token = tmp;
		}
		free(token);
		token = NULL;
	}
}

void	free_commands(t_commands *command)
{
	t_commands *tmp;

	if (command)
	{
		tmp = command;
		while (tmp)
		{
			tmp = tmp -> next;
			if (command -> name)
				free(command -> name);
			if (command -> args)
				free_arr(command -> args);
			//command -> args = NULL;
			free(command);
			command = tmp;
		}
		free (command);
		command = NULL;
	}
}

void	free_shell(t_shell *shell)
{
	free_tokens(shell -> token);
	//free_env(shell -> env);
	//free_env(shell -> exp);
	//free_commands(shell -> command);
	free(shell -> input);
	free(shell -> pwd);
	free(shell -> oldpwd);
	shell -> token_count = 0;
	shell -> token = NULL;
	shell -> input = NULL;
	shell -> command = NULL;
	//shell -> env = NULL;
	//shell -> exp = NULL;
	shell -> pwd = NULL;
	shell -> oldpwd = NULL;
}


void	free_str(char	*str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	free_arr(char **arr)
{
	if (*arr)
	{
		free(*arr);
		*arr = NULL;
	}
	arr = NULL;
}
