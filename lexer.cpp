#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#include <string.h>
#include <base/string.h>
#include <base/listnode.h>

#include "lexer.h"
#include "token.h"

static char operators[] = "{}\"+=";

Lexer :: Lexer()
{
	this->reset();
	this->tokens = NULL;
}

Lexer :: ~Lexer()
{
	for (Token *token = this->tokens; token != NULL; token = (Token *) token->next)
	{
		delete token;
	}
}

void Lexer :: reset()
{
	this->buffer.clear();
}

bool Lexer :: parse(FILE *file)
{
	/* Go through each character of the file, appending it 	*
	 * to a buffer. When it is determined that the end of a	*
	 * token has been reached, create it.					*/
		
	for (int32_t byte; (byte = fgetc(file)) != EOF;)
	{
		/* Both of these decisions cause us to create a token	*
		 * from what was already in the buffer because of the	*
		 * byte that we've just read.							*/
		
		if (isspace(byte))
		{
			/* If we have encountered whitespace, we have either reached		*
			 * the end of a token or are within a larger block of whitespace.	*
			 * In the former case, we need the token to be appended to the list,*
			 * and in the latter case the function will return immediately 		*
			 * since buffer is empty.											*/
			
			this->create_token();
			continue;
		}
		if (strchr(operators, byte) != NULL)
		{
			/* If we've encountered an operator, we have to save the pending token first.	*/
			 
			this->create_token();
		}
		
		this->buffer.append_c(byte);
		
		/* The following decisions are made based		*
		 * upon the text in the buffer, now that the	*
		 * byte has been added to it.					*/
		 
		if (strchr(operators, byte) != NULL)
		{
			/* If the current character is an operator, append it to the list.		*
			 * Multiple-character operators are dealt with by ->create_token() too.	*/
			
			this->create_token();
		}

	}
	
	return true;
}

void Lexer :: create_token()
{
	/* Here we make the judgement of what the token actually *is*, and then add it to the list */
	
	Token *token = new Token();
	
	if (this->buffer.length() == 0)
	{
		return;
	}
	
	/* Literals */
	else if (BString::equals(&this->buffer, "\""))
	{
		/* We're either at the start of the end of a string literal */
		token->type = STR_LITERAL;
		
//		if ()
	}
	
	/* Brackets */
	else if (BString::equals(&this->buffer, "="))
	{
		token->type = ASSIGNMENT;
	}
	else if (BString::equals(&this->buffer, "+"))
	{
		token->type = ADDITION;
	}
	else if (BString::equals(&this->buffer, "{"))
	{
		token->type = DICT_OPEN;
	}
	else if (BString::equals(&this->buffer, "}"))
	{
		token->type = DICT_CLOSE;
	}
	
	/* Else it must be an identifier */
	else
	{
		token->type = IDENTIFIER;
		token->text.set(&this->buffer);
	}
	
	Token::print(token);
	BListNode::append(token, (BListNode **) &this->tokens);
	
	this->reset();
	return;

error:
	delete token;
	this->reset();
}
