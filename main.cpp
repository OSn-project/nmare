#include <stdio.h>
#include <stdlib.h>
#include <base/string.h>

#include "lexer.h"

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		printf("%s <file>\n", argv[0]);
		exit(1);
	}
	
	FILE *file = fopen(argv[1], "r");
	
	if (file == NULL)
	{
		fprintf(stderr, "[ERROR] Error opening file:\n%s\n", argv[0]);
		exit(1);
	}
	
	{
		Lexer lexer;
		
		lexer.parse(file);
	}
	
	fclose(file);
	
    return 0;
}
