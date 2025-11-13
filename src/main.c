#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"

int main() {
    Tokenizer* tokenizer = tokenizer_create("100 +2*3/4*4", 12);
    
    Token token;
    while ((token = tokenizer_next(tokenizer)).type != TOKEN_EOF) {
       printf("%s \n", token.lexeme ? token.lexeme : "NULL"); 
    } 

    tokenizer_free(tokenizer);
}
