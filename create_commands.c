#include "./include/minishell.h"

void	create_commands(t_shell *shell)
{
	t_token		*tkn;
	t_commands	*tmp;

	if (!shell -> token)
		error(ALLOCATION_ERR, shell);
	tmp = shell -> command;
	tkn = shell -> token;
	if (tkn)
	{
		printf("%s\n",tkn -> value);// h | t l
		while (tkn)
		{
			if (!(tmp))
			{
				tmp = create_command(shell -> token -> value);
				shell -> command = tmp;
				if (!(shell -> command))
					error(ALLOCATION_ERR, shell);

			}
			else
			{
				add_command(&tkn, &tmp, shell);
				printf("%s\n",tkn -> value);
				//get_args(&tkn, &tmp, shell);
					///freeshit is callinggg
			}
			get_args(&tkn, &tmp, shell); //freeshit token
			tkn = tkn -> next;
		}
	}
}


void	add_args(t_token **token, t_shell *shell, int args_cnt)
{
	t_commands	*tmp;
	int	i;

	i = 0;
	tmp = shell -> command;
	if (!tmp)
		return ;
	while (tmp -> next)
		tmp = tmp -> next;
	if (args_cnt)
	{
		tmp -> args = malloc (sizeof(char *) * (args_cnt + 1));
		if (!tmp -> args)
			error(ALLOCATION_ERR, shell);
		while (args_cnt && (*token) -> next)
		{
			tmp -> args[i]= ft_strdup((*token) ->next-> value);
			if (!tmp -> args[i])
				error(ALLOCATION_ERR,shell);
			i++;
			args_cnt--;
			(*token) = (*token) -> next;
		}
		tmp -> args[i] = NULL;
		tmp = tmp -> next;
	}
}

// void add_args(t_token **token, t_shell *shell, int args_cnt)
// {
//     t_commands *current_command;
//     int i = 0;

//     current_command = shell->command;
//     // Ensure the command list is not empty
//     if (!current_command)
//         return;

//     // Traverse to the last command (if needed)
//     while (current_command->next)
//         current_command = current_command->next;

//     // Assuming we are adding arguments to the last command
//     if (args_cnt > 0)
//     {
//         // Allocate space for args in the command node if not already allocated
//         current_command->args = malloc((args_cnt + 1) * sizeof(char*));
//         if (!current_command->args)
//         {
//             perror("Failed to allocate memory for args");
//             exit(EXIT_FAILURE);
//         }

//         i = 0;
//         while (args_cnt > 0 && (*token)->next)
//         {
//             current_command->args[i] = ft_strdup((*token)->next->value);
//             if (!current_command->args[i])
//             {
//                 perror("Failed to duplicate token value");
//                 exit(EXIT_FAILURE);
//             }
//             i++;
//             args_cnt--;
//             *token = (*token)->next;
//         }
//         // Null-terminate the args array
//         current_command->args[i] = NULL;
//     }
// }



void get_args(t_token **token, t_commands **command, t_shell *shell)
{
    int args_count = 0;
    t_token *tmp;
	(void)command;

    if (!token || !*token || !shell || !shell->token)
        return;

    tmp = *token;
	printf("tmp = %s\n",tmp -> value);
    while (tmp && tmp -> next && tmp->next ->type != TOKEN_PIPE)
    {
        tmp = tmp->next;
        args_count++;
    }
	add_args(token, shell, args_count);
    // shell->command->args = malloc(sizeof(char *) * (args_count + 1));
    // if (!shell->command->args)
    //     return;
    // tmp = (*token)->next;
    // while ((tmp && tmp->type != TOKEN_PIPE))
    // {
    //     shell->command->args[i] = ft_strdup(tmp->value);
    //     tmp = tmp->next;
	// 	(*token) = (*token) -> next;
    //     i++;
    // }
    // shell->command->args[i] = NULL;
}


void	add_command(t_token **tkn, t_commands **tmp, t_shell *shell)
{
	if (!ft_strcmp((*tkn) -> value, "|"))
	{
		while ((*tmp) -> next)
			(*tmp) = (*tmp) -> next;
		(*tmp) -> next = create_command((*tkn) -> next -> value);
		if (!((*tmp) -> next))
			free_shell(shell);
		(*tmp) -> next -> prev = *tmp;
		// printf("prev = %s  , curr = %s \n", ((*tmp) -> next -> prev) -> name, ((*tmp) -> next -> name));
		(*tkn) = (*tkn) -> next;
	}
}




t_commands	*create_command(char *value)
{
	t_commands	*command;

	if (!value)
		return (NULL);
	command = malloc(sizeof(t_commands));
	if (!command)//allocation failed;
		return (NULL);
	command -> name = ft_strdup(value);
	command -> args = NULL;
	command -> next = NULL;
	command -> prev = NULL;
	if (!command)
	{
		free_commands(command);
		return (NULL);//alocation failed
	}
	command -> next = NULL;
	return (command);
}
