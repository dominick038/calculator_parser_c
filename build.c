#define NOBUILD_IMPLEMENTATION
#include "nobuild.h"

int main(int argc, char** argv) {
    GO_REBUILD_URSELF(argc, argv);
    
    CMD("gcc", "-fsanitize=address", 
        "-g", "-fno-omit-frame-pointer",
        "-Wall", "-Wextra", "-g",
        "-I./headers",
        "src/main.c", "src/tokenizer.c",
        "src/token_stack.c", "src/token_queue.c",
        "-o", "./bin/calculator_parser_c", NULL);
    
    return 0;
}
