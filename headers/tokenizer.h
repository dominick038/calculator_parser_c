#ifndef __TOKENIZER__
#define __TOKENIZER__

#include <stddef.h>

typedef struct Tokenizer Tokenizer;

#define TOKEN_COUNT 7
typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    double value;
    char* lexeme;
} Token;

Tokenizer* tokenizer_create(const char* input, size_t length); 

Token tokenizer_next(Tokenizer* tok);

void token_free(Token tok);

void tokenizer_free(Tokenizer* tok);

#endif
