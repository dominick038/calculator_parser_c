#ifndef __PARSER__
#define __PARSER__

#include "tokenizer.h"

typedef struct Parser Parser;

Parser* parser_create();

const char* parser_evalutate_token_stream(Tokenizer* tokenizer);

void parser_free(Parser* parser);

#endif
