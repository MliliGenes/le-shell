/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssbaytri <ssbaytri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:44:36 by ssbaytri          #+#    #+#             */
/*   Updated: 2025/05/13 23:51:58 by ssbaytri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

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

static int	word_count(char *s, char sep)
{
	int	i;
	int	in_word;
	int	cp;

	i = 0;
	in_word = 0;
	cp = 0;
	while (s[i])
	{
		if (s[i] == sep)
		{
			in_word = 0;
		}
		else if (s[i] != sep && in_word == 0)
		{
			in_word = 1;
			cp++;
		}
		i++;
	}
	return (cp);
}

static void	*free_arr(char **arr, int i)
{
	while (--i >= 0)
		free(arr[i]);
	free(arr);
	return (NULL);
}

static char	**filling_arr(char c, const char *s, char **arr, int words)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	while (i < words)
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		arr[i] = ft_substr(s, (unsigned int)start, (size_t)(end - start));
		if (!arr[i])
			return (free_arr(arr, i));
		start = end + 1;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**splitted;

	if (!s)
		return (NULL);
	if (!*s)
	{
		splitted = (char **)malloc(sizeof(char *));
		if (!splitted)
			return (NULL);
		splitted[0] = NULL;
		return (splitted);
	}
	words = word_count((char *)s, c);
	splitted = (char **)malloc((words + 1) * sizeof(char *));
	if (!splitted)
		return (NULL);
	return (filling_arr(c, s, splitted, words));
}

t_entry *create_entry(char *value)
{
	t_entry	*new;

	new = malloc(sizeof(t_entry));
	if (!new)
		return (NULL);
	new->value = strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->entry_len = strlen(new->value);
	new->next = NULL;
	return (new);
}

void free_entry_list(t_entry *head)
{
	t_entry	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

void add_back_entry(t_entry **head, t_entry *new)
{
	t_entry	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_entry *get_all_entries()
{
	DIR *dir;
	struct dirent *entry;
	t_entry *head;
	t_entry *new;

	head = NULL;
	dir = opendir(".");
	if (!dir)
		return (perror("opendir"), NULL);
	entry = readdir(dir);
	while (entry)
	{
		new =create_entry(entry->d_name);
		if (!new)
			return (free_entry_list(head) ,NULL);
		add_back_entry(&head, new);
		entry = readdir(dir);
	}
	return (closedir(dir), head);
}

int counter(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int match_split(char *filename, char **pieces)
{
	int i = 0;
	char *found;

	while (pieces[i])
	{
		found = strnstr(filename, pieces[i], strlen(filename));
		if (!found)
			return (0);
		filename = found + strlen(pieces[i]);
		i++;
	}
	return (1);
}

static int match(char *filename, char *pattern)
{
	if (strcmp(pattern, "*") == 0)
		return (1);
	if (pattern[0] == '*' && pattern[strlen(pattern) - 1] != '*' && counter(pattern, '*') == 1)
	{
		char *text = pattern + 1;
		int len = strlen(text);
		int file_len = strlen(filename);
		if (file_len >= len && strcmp(filename + file_len - len, text) == 0)
			return (1);
	}
	else if (pattern[strlen(pattern) - 1] == '*' && pattern[0] != '*' && counter(pattern, '*') == 1)
    {
        int len = strlen(pattern) - 1;
        if (strncmp(filename, pattern, len) == 0)
            return (1);
    }
	else if (pattern[0] == '*' && pattern[strlen(pattern) - 1] == '*' && counter(pattern, '*') == 2)
	{
		char *text = ft_substr(pattern, 1, strlen(pattern) - 2);
		if (!text)
			return (0);
		if (strnstr(filename, text, strlen(filename)))
		{
			free(text);
			return (1);
		}
		free(text);
	}
	else
	{
		char **split = ft_split(pattern, '*');
		if (!split)
			return (0);
		if (match_split(filename, split))
		{
			return (1);
		}
	}
	return (0);
}

void filter_entries_by_pattern(t_entry *entries, char *pattern) {
    t_entry *current = entries;
    while (current) {
        if (match(current->value, pattern)) {
            printf("Match: %s\n", current->value);
        }
        current = current->next;
    }
}

int main(int argc, char **argv)
{
    t_entry *entries = get_all_entries();
	char *pattern = "e*.c";
    filter_entries_by_pattern(entries, pattern);
    free_entry_list(entries);
}


