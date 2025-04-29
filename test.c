#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct var
{
	char		*key;
	char		*value;
	struct var	*next;
}				t_env_var;

t_env_var	*create_var(const char *key, const char *value)
{
	t_env_var	*new_var;

	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return (NULL);
	new_var->key = strdup(key);
	new_var->value = strdup(value);
	new_var->next = NULL;
	return (new_var);
}

void	free_var_list(t_env_var *head)
{
	t_env_var	*current;
	t_env_var	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

char	*find_env_var(t_env_var *env_vars, const char *key)
{
	while (env_vars != NULL)
	{
		if (strcmp(env_vars->key, key) == 0)
			return (env_vars->value);
		env_vars = env_vars->next;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*ptr;

	s_len = strlen(s);
	if (start > s_len)
		return (strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

typedef struct s_expansion
{
	char		*input;
	char		*output;
	int			s_quote;
	int			d_quote;
	int			i_index;
	int			o_index;
	int			len;
	t_env_var	*vars;
}				t_expansion;

void	init_expansion(t_expansion *exp, char *input, t_env_var *vars)
{
	exp->input = input;
	exp->len = strlen(input);
	exp->s_quote = 0;
	exp->d_quote = 0;
	exp->i_index = 0;
	exp->o_index = 0;
	exp->vars = vars;
}

void	update_quote_state(t_expansion *exp, char current_char)
{
	if (current_char == '\'' && !exp->d_quote)
		exp->s_quote = !exp->s_quote;
	if (current_char == '\"' && !exp->s_quote)
		exp->d_quote = !exp->d_quote;
}

void	process_variable_length(t_expansion *exp)
{
	int		start;
	char	*key;
	char	*value;

	exp->i_index++;
	start = exp->i_index;
	exp->len--;
	while (exp->input[exp->i_index] && (isalnum(exp->input[exp->i_index])
			|| exp->input[exp->i_index] == '_'))
	{
		exp->len--;
		exp->i_index++;
	}
	key = ft_substr(exp->input, start, exp->i_index - start);
	value = find_env_var(exp->vars, key);
	if (value)
		exp->len += strlen(value);
	free(key);
}

void	calculate_expanded_length(t_expansion *exp)
{
	while (exp->input[exp->i_index])
	{
		update_quote_state(exp, exp->input[exp->i_index]);
		if (!exp->s_quote && exp->input[exp->i_index] == '$'
			&& (isalpha(exp->input[exp->i_index + 1]) || exp->input[exp->i_index
				+ 1] == '_'))
			process_variable_length(exp);
		else
			exp->i_index++;
	}
	exp->i_index = 0;
}

char	*extract_var_name(t_expansion *exp)
{
	int	start;
	int	length;

	start = exp->i_index;
	length = 0;
	while (exp->input[exp->i_index] && (isalnum(exp->input[exp->i_index])
			|| exp->input[exp->i_index] == '_'))
	{
		exp->i_index++;
		length++;
	}
	return (ft_substr(exp->input, start, length));
}

void	expand_variable(t_expansion *exp)
{
	char	*key;
	char	*value;
	int		value_index;

	value_index = 0;
	exp->i_index++;
	key = extract_var_name(exp);
	value = find_env_var(exp->vars, key);
	if (value)
	{
		while (value[value_index])
			exp->output[exp->o_index++] = value[value_index++];
	}
	free(key);
}

void	expand_vars(char *input, t_env_var *vars)
{
	t_expansion	exp;

	init_expansion(&exp, input, vars);
	calculate_expanded_length(&exp);
	exp.output = (char *)malloc(exp.len + 1);
	if (!exp.output)
		return ;
	while (input[exp.i_index])
	{
		update_quote_state(&exp, input[exp.i_index]);
		if (!exp.s_quote && input[exp.i_index] == '$'
			&& (isalpha(input[exp.i_index + 1]) || input[exp.i_index
				+ 1] == '_'))
			expand_variable(&exp);
		else
			exp.output[exp.o_index++] = input[exp.i_index++];
	}
	exp.output[exp.o_index] = 0;
	printf("before: %s\n", input);
	printf("after: %s\n", exp.output);
	free(exp.output);
}

int	main(void)
{
	t_env_var *env_vars;
	t_env_var *current;
	char *test1;
	char *test2;
	char *test3;
	char *test4;
	char *test5;

	env_vars = create_var("HOME", "/home/user");
	current = env_vars;
	current->next = create_var("USER", "johndoe");
	current = current->next;
	current->next = create_var("VAR", "s -al");
	current = current->next;
	current->next = create_var("PATH", "/usr/bin:/bin");
	current = current->next;
	current->next = create_var("SHELL", "/bin/bash");
	current = current->next;
	current->next = create_var("TERM", "xterm");
	current = current->next;
	current->next = create_var("PWD", "/home/user/projects");
	current = current->next;
	current->next = create_var("LANG", "en_US.UTF-8");
	test1 = "l$VAR";
	test2 = "Current directory: $PWD using $SHELL";
	test3 = "Missing variable: $NONEXISTENT should be skipped";
	test4 = "Multiple variables: $USER is using $TERM in $HOME";
	test5 = "$VAR at the beginning and at the end $PWD";
	printf("Environment Variables:\n");
	current = env_vars;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	printf("\n");
	printf("Test Strings:\n");
	expand_vars(test1, env_vars);
	expand_vars(test2, env_vars);
	expand_vars(test3, env_vars);
	expand_vars(test4, env_vars);
	expand_vars(test5, env_vars);
	free_var_list(env_vars);
	return (0);
}