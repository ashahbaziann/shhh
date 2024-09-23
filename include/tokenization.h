#ifndef TOKENIZATION_H
 #define TOKENIZATION_H

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
} t_token_type;

typedef enum	s_lexer_state
{
	DEFAULT,
	IN_SINGLE_QUOTES,
	IN_DOUBLE_QUOTES,
} t_lexer_state;

typedef struct s_token
{

	char			*value;
	char			*var_value;
	int				space;
	t_token_type	type;
	t_lexer_state	state;
	struct s_token	*next;
} t_token;
 
typedef struct s_commands
{
	char				*name;
	//char				*flags;
	char				**args;
	struct s_commands	*next;
	struct s_commands	*prev;
} t_commands;


#endif
