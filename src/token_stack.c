#include "token_stack.h"
#include "tokenizer.h"
#include <stddef.h>
#include <stdlib.h>

#define DEFAULT_TOKEN_STACK_SIZE 32

struct TokenStack
{
    Token* arr;
    size_t top;
    size_t capacity;
};

TokenStack* token_stack_create()
{
    TokenStack* result_token_stack = malloc(sizeof(TokenStack));
    
    result_token_stack->arr      = malloc(sizeof(Token) * DEFAULT_TOKEN_STACK_SIZE);
    result_token_stack->capacity = DEFAULT_TOKEN_STACK_SIZE;
    result_token_stack->top      = 0;

    return result_token_stack;
}

static void resize_array(TokenStack* tokstk, size_t new_capacity)
{
    Token* tmp = realloc(tokstk->arr, sizeof(Token) * new_capacity);
    if (tmp != NULL)
    {
        tokstk->arr      = tmp;
        tokstk->capacity = new_capacity;
    }
}

void token_stack_push(TokenStack *tokstk, Token tok)
{
    if (tokstk->top >= tokstk->capacity)
        resize_array(tokstk, tokstk->capacity * 2);

    tokstk->arr[tokstk->top] = tok;
    tokstk->top++;
}

int token_stack_pop(TokenStack *tokstk, Token* tokout)
{
    if (tokstk->top == 0) 
        return -1;
   
    Token tok = tokstk->arr[tokstk->top-1];
    *tokout = tok; 

    tokstk->top--;

    return 0;
}

int token_stack_peek(TokenStack *tokstk, Token* tokout)
{
    if (tokstk->top == 0)
        return -1;

    Token tok = tokstk->arr[tokstk->top-1];
    *tokout = tok; 

    return 0;
}

bool token_stack_is_empty(TokenStack* tokstk)
{
    return tokstk->top == 0;
}

void token_stack_free(TokenStack* tokstk)
{
    if (!tokstk) return;

    if (tokstk->arr)
    {
        for (size_t i = 0; i < tokstk->top; i++) {
            Token tok = tokstk->arr[i];
            
            token_free(tok);
        }

        free(tokstk->arr);
    }

    free(tokstk);
}
