#include "..nclude/parsing.h"

void	update_quote_status(char c, bool *in_single, bool *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (c == '"' && !(*in_single))
		*in_double = !(*in_double);
}	

bool	is_in_quote(bool in_single, bool in_double)
{
	return (in_single || in_double);
}

int	find_word_start(char *joint, int end, bool *in_single, bool *in_double)
{
	while (joint[end] && is_white_space(joint[end]) && !is_in_quote(*in_single,
			*in_double))
		end++;
	return (end);
}

int	find_word_end(char *joint, int end, bool *in_single, bool *in_double)
{
	while (joint[end] && (!is_white_space(joint[end]) || is_in_quote(*in_single,
				*in_double)))
	{
		update_quote_status(joint[end], in_single, in_double);
		end++;
	}
	return (end);
}
