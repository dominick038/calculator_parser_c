#ifndef __TOKEN_STACK__
#define __TOKEN_STACK__

#include <stdbool.h>

#include "tokenizer.h"

typedef struct TokenStack TokenStack;

TokenStack* token_stack_create();

void token_stack_push(TokenStack* tokstk, Token tok);

int token_stack_pop(TokenStack *tokstk, Token* tokout);

int token_stack_peek(TokenStack *tokstk, Token* tokout);

bool token_stack_is_empty(TokenStack* tokstk);

void token_stack_free(TokenStack* tokstk);

#endif
