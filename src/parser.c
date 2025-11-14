#include <stdio.h>
#include <stdlib.h>
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

const char* parser_evaluate(Tokenizer *tokenizer)
{
    TokenStack* operator_stack = token_stack_create();
    TokenQueue* output_queue   = token_queue_create();

    if (!operator_stack || !output_queue) {
        return NULL;
    }

    Token token;
    while ((token = tokenizer_next(tokenizer)).type != TOKEN_EOF) {
        if (token.type == TOKEN_NUMBER)
        {
            token_queue_enqueue(output_queue, token);
        }
        else
        {
            Token top_token;
            while (!token_stack_is_empty(operator_stack) &&
                   token_stack_peek(operator_stack, &top_token) == 0 &&
                   presedence[top_token.type] >= presedence[token.type])
            {
                token_stack_pop(operator_stack, &top_token);
                token_queue_enqueue(output_queue, top_token);
            }

            token_stack_push(operator_stack, token);
        }
    }

    Token remaining;
    while (token_stack_pop(operator_stack, &remaining) == 0) {
        token_queue_enqueue(output_queue, remaining);
    }

    double value_stack[256];
    int stack_top = -1;

    Token rpn_token;
    while (token_queue_dequeue(output_queue, &rpn_token) == 0) {
        if (rpn_token.type == TOKEN_NUMBER) {
            value_stack[stack_top + 1] = rpn_token.value;
            stack_top = stack_top + 1;
        } else {
            double right = value_stack[stack_top];
            stack_top = stack_top - 1;
            double left = value_stack[stack_top];
            stack_top = stack_top - 1;

            double result;
            switch (rpn_token.type) {
                case TOKEN_PLUS:     result = left + right; break;
                case TOKEN_MINUS:    result = left - right; break;
                case TOKEN_MULTIPLY: result = left * right; break;
                case TOKEN_DIVIDE:   result = left / right; break;
                default: exit(-1);
            }

            value_stack[stack_top + 1] = result;
            stack_top = stack_top + 1;
        }
        token_free(rpn_token);
    }
    
    token_stack_free(operator_stack);
    token_queue_free(output_queue);

    static char result_buffer[64];
    snprintf(result_buffer, sizeof(result_buffer), "%g", value_stack[stack_top]);
    return result_buffer;
}
