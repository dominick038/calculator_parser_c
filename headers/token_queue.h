#ifndef __TOKEN_QUEUE__
#define __TOKEN_QUEUE__

#include "tokenizer.h"

typedef struct TokenQueue TokenQueue;

TokenQueue* token_queue_create();

int token_queue_enqueue(TokenQueue* tokq, Token tok);

int token_queue_dequeue(TokenQueue* tokq, Token* tokout);

int token_queue_peek(TokenQueue* tokq, Token* tokout);

void token_queue_free(TokenQueue* tokq);

#endif
