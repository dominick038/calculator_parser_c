#include "token_queue.h"
#include "tokenizer.h"
#include <stdlib.h>

#define DEFAULT_ARR_SIZE 32

struct TokenQueue {
    Token* arr;
    size_t front;
    size_t back;
    size_t size;
    size_t capacity;
};

TokenQueue* token_queue_create()
{
    TokenQueue* result = malloc(sizeof(TokenQueue));
    if (!result) 
        return NULL;
    
    result->back     = 0;
    result->front    = 0;
    result->size     = 0;
    result->capacity = DEFAULT_ARR_SIZE;
    result->arr      = malloc(sizeof(Token) * DEFAULT_ARR_SIZE);

    if (!result->arr)
        return NULL;

    return result;
}

int token_queue_enqueue(TokenQueue *tokq, Token tok)
{
    
}

int token_queue_dequeue(TokenQueue *tokq, Token *tok) 
{

}

int token_queue_peek(TokenQueue *tokq, Token *tok)
{

}

void token_queue_free(TokenQueue *tokq)
{
    
}
