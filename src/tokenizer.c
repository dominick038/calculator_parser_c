#include "tokenizer.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tokenizer {
    const char* input;
    size_t pos; 
    size_t length;
    Token current;
};

Tokenizer* tokenizer_create(const char* input, size_t length)
{
    Tokenizer* result = malloc(sizeof(Tokenizer));
    if (!result) return NULL;

    result->input   = input;
    result->length  = length;
    result->pos     = 0;

    return result;
}

Token extract_digit(Tokenizer *tok) 
{
    char token_buffer[22];
    size_t i = 0;
    while (tok->pos < tok->length)
    {
        char current = tok->input[tok->pos];
        if (!isdigit(current)) break;

        token_buffer[i] = current;
        
        i++;
        tok->pos++;
    }
    token_buffer[i] = '\0';

    char* copy = malloc(strlen(token_buffer) + 1);
    strcpy(copy, token_buffer);

    Token result_token;
    result_token.lexeme = copy;
    result_token.type   = TOKEN_NUMBER;
    result_token.value  = atoi(copy);

    return result_token;
}

Token tokenizer_next(Tokenizer* tok)
{
    while (tok->pos < tok->length)
    {
        char current = tok->input[tok->pos];

        if (isspace(current))
        {
            tok->pos++;
            continue;
        }

        if (isdigit(current))
        {
            return extract_digit(tok);
        }

        if (current == '+')
        {
            Token pls_tok = { TOKEN_PLUS, 0.0, "+" };

            tok->pos++;
            tok->current = pls_tok; 

            return pls_tok;
        }

        if (current == '-')
        {
            Token min_tok = { TOKEN_MINUS, 0.0, "-" };
                                                           
            tok->pos++;
            tok->current = min_tok; 
                                                           
            return min_tok;
        }

        if (current == '*')
        {
            Token mult_tok = { TOKEN_MULTIPLY, 0.0, "*" };
           
            tok->pos++;
            tok->current = mult_tok; 

            return mult_tok;
        }

        if (current == '/')
        {
            Token div_tok = { TOKEN_DIVIDE, 0.0, "/" };
                                                           
            tok->pos++;
            tok->current = div_tok; 
                                                           
            return div_tok;
        }

        tok->pos++;
    }

    Token eof = { TOKEN_EOF, 0.0, NULL };
    tok->current = eof; 
    return eof;
}

void token_free(Token tok)
{
    if (tok.type == TOKEN_NUMBER && tok.lexeme)
    {
        free(tok.lexeme);
        tok.lexeme = NULL;
    }
}

void tokenizer_free(Tokenizer* tok) 
{
    free(tok);
}
