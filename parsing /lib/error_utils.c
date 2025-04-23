#include "../include/dependencies.h"

void	print_syntax_error(const char *token, const char *reason)
{
	printf("\033[1;31m ✗ SYNTAX ERROR\033[0m at '\033[1;33m%s\033[0m' → %s\n",
		token, reason);
}
