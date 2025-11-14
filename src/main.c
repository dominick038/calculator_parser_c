#include <stdio.h>
#include <string.h>
#include "tokenizer.h"
#include "parser.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 0;
    }

    char* expression = argv[1];
    Tokenizer* tokenizer = tokenizer_create(expression, strlen(expression));

    printf("result: %s\n", parser_evaluate(tokenizer));

    tokenizer_free(tokenizer);
}
