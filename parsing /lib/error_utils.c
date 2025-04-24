#include "../include/dependencies.h"

void print_syntax_error(const char *token, const char *reason)
{
    printf("%s⚠️  SYNTAX ERROR %s » Token: %s%s%s » Reason: %s\n", RED, RESET, YELLOW, token, RESET, reason);
}
