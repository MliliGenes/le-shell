#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct var
{
	char		*key;
	char		*value;
	struct var	*next;
}				var;

// Utility function to create a new var node
var	*create_var(const char *key, const char *value)
{
	var	*new_var;

	new_var = (var *)malloc(sizeof(var));
	if (!new_var)
		return (NULL);
	new_var->key = strdup(key);
	new_var->value = strdup(value);
	new_var->next = NULL;
	return (new_var);
}

// Function to free the linked list
void	free_var_list(var *head)
{
	var	*current;
	var	*next;

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

char	*find_env_var(var *env_vars, const char *key)
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

void	expand_vars(char *input, var *vars)
{
	int		total_len;
	int		i;
	int		start;
	char	*key;
	char	*value;
	char	*new_input;
	int		j;
	int		k;

	i = 0;
	total_len = strlen(input);
	while (input[i])
	{
		if (input[i] == '$' && isalpha(input[i + 1]))
		{
			i++;
			start = i;
			total_len--;
			while (input[i] && (isalnum(input[i]) || input[i] == '_'))
			{
				total_len--;
				i++;
			}
			key = ft_substr(input, start, i - start);
			value = find_env_var(vars, key);
			printf("key: %s\nvalue: %s\n", key, value);
			if (value)
				total_len += strlen(value);
			continue ;
		}
		i++;
	}
	new_input = malloc(total_len);
	i = 0;
	j = 0;
	k = 0;
	while (input[i])
	{
		if (input[i] == '$' && isalpha(input[i + 1]))
		{
			k = i + 1;
			start = k;
			while (input[k] && (isalnum(input[k]) || input[k] == '_'))
				i++;
			key = ft_substr(input, start, k - start);
			i += strlen(key) + 1;
			value = find_env_var(vars, key);
			k = 0;
			while (value[k])
				new_input[j++] = value[k++];
		}
		else
		{
			new_input[j++] = input[i++];
		}
		i++;
	}
	printf("%s => total lenth of input after expansion :%d", input, total_len);
	printf("%s", new_input);
}

int	main(void)
{
	// Create several variables for testing
	var *env_vars = create_var("HOME", "/home/user");
	var *current = env_vars;

	current->next = create_var("USER", "johndoe");
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

	char *test1 = "$USER $HOME";
	char *test2 = "Current directory: $PWD using $SHELL";
	char *test3 = "Missing variable: $NONEXISTENT should be skipped";
	char *test4 = "Multiple variables: $USER is using $TERM in $HOME";
	char *test5 = "$VAR at the beginning and at the end $PWD";

	printf("Environment Variables:\n");
	current = env_vars;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	printf("\n");

	printf("Test Strings:\n");
	// printf("1: %s\n", test1);
	// printf("2: %s\n", test2);
	// printf("3: %s\n", test3);
	// printf("4: %s\n", test4);
	// printf("5: %s\n", test5);

	// TODO: Call your expand_vars function here and print the results
	expand_vars(test1, env_vars);

	// Clean up
	free_var_list(env_vars);

	return (0);
}