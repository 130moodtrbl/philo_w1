#include <string.h>
#include <stdio.h>

int main(void)
{
	char str[] = "\e[1;95mIssue:\e gettimeofday() failed (utils.c)\n";
	printf("%lu", strlen(str));
}