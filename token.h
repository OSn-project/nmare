#ifndef __NMARE_TOKEN_H__
#define __NMARE_TOKEN_H__

#include <osndef.h>
#include <base/string.h>
#include <base/listnode.h>

enum TokenType
{
	UNKNOWN = 0,
	
	IDENTIFIER,
	STR_LITERAL,
	
	ASSIGNMENT,
	ADDITION,
	
	DICT_OPEN,
	DICT_CLOSE,
};

struct Token : public BListNode
{
	TokenType type;
	BString text;
	
	/* Functions */
	static const char *type_name(TokenType type);
	static void print(Token *token);
};

#endif
