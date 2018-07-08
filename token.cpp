#include <stdlib.h>
#include <base/listnode.h>

#include "token.h"

const char *Token :: type_name(TokenType type)
{
	switch (type)
	{
		case IDENTIFIER:
			return "IDENTIFIER";
		case STR_LITERAL:
			return "STR_LITERAL";
		case ASSIGNMENT:
			return "ASSIGNMENT";
		case ADDITION:
			return "ADDITION";
		case DICT_OPEN:
			return "DICT_OPEN";
		case DICT_CLOSE:
			return "DICT_CLOSE";
		
		default:
			return "UNKNOWN";
	}
}

#include <stdio.h>
void Token :: print(Token *token)
{
	printf("{type = %s, text = \"%s\"}\n", Token::type_name(token->type), token->text.c_str());
}
