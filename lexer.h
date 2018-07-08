#ifndef __NMARE_PARSER_H__
#define __NMARE_PARSER_H__

#include <stdio.h>
#include <base/string.h>

#include "token.h"

class Lexer
{
	BString buffer;			// Text since the last token that hasn't been parsed yet
	
	enum {
		NORMAL,
		IGNORE_LINE,	// Ignore until the end of the line
		READ_LITERAL	// Read into the buffer until the next `"`
	} state;
	
public:
	Token *tokens;
	
	Lexer();
	~Lexer();
	
	bool parse(FILE *file);

private:
	void read_literal();
	
	void reset();			// Clears the buffer of the currently read token
	void create_token();	// Create a token from the current state.
	void add(Token *tok);
};

#endif
