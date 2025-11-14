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

static int resize_array(TokenQueue* tokq, size_t new_capacity)
{
    Token* new_arr = malloc(sizeof(Token) * new_capacity);

    if (!new_arr)
        return -1;

    size_t idx = 0;
    for (size_t i = 0; i < tokq->size; i++) {
        new_arr[idx++] = tokq->arr[(tokq->front + i) % tokq->capacity];
    }

    free(tokq->arr);
    tokq->arr = new_arr;
    tokq->capacity = new_capacity;
    tokq->front = 0;
    tokq->back = tokq->size;

    return 0;
}

int token_queue_enqueue(TokenQueue *tokq, Token tok)
{
    if (tokq->capacity == tokq->size)
    {
        if (resize_array(tokq, tokq->capacity * 2) != 0)
            return -1;
    }

    size_t i = tokq->back;
    tokq->arr[i] = tok;
    tokq->back = (i + 1) % tokq->capacity;
    tokq->size++;

    return 0; 
}

int token_queue_dequeue(TokenQueue *tokq, Token *tokout) 
{
    if (tokq->size == 0)
    {
        return -1;
    }

    size_t i = tokq->front;
    Token tok = tokq->arr[i];
    *tokout = tok;
    tokq->front = (i + 1) % tokq->capacity;
    tokq->size--;

    return 0;
}

int token_queue_peek(TokenQueue *tokq, Token *tokout)
{
    if (tokq->size == 0)
    {
        return -1;
    }

    size_t i = tokq->front;
    Token tok = tokq->arr[i];
    *tokout = tok;

    return 0;
}

void token_queue_free(TokenQueue *tokq)
{
    if (!tokq)
        return;

    if (tokq->arr)
    {
        for (size_t i = 0; i < tokq->size; i++) {
            Token tok = tokq->arr[(tokq->front + i) % tokq->capacity];

            token_free(tok);
        }

        free(tokq->arr);
    }

    free(tokq);
}


