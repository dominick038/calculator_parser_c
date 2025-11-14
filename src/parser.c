#include "parser.h"
#include "tokenizer.h"
#include "token_stack.h"
#include "token_queue.h"

const int presedence[TOKEN_COUNT] = {
    [TOKEN_PLUS]     = 1,
    [TOKEN_MINUS]    = 1,
    [TOKEN_MULTIPLY] = 2,
    [TOKEN_DIVIDE]   = 2
};

const char* parser_evalutate(Tokenizer *tokenizer)
{
    TokenStack* operator_stack = token_stack_create();
    TokenQueue* output_queue   = token_queue_create();

    Token token;
    while ((token = tokenizer_next(tokenizer)).type != TOKEN_EOF) {
        if (token.type == TOKEN_NUMBER) 
        {
            token_queue_enqueue(output_queue, token);
        }
        else 
        {
             
        }
    } 
}
