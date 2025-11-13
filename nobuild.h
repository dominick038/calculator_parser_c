#ifndef NOBUILD_H_
#define NOBUILD_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Check if we need to rebuild ourselves
#define GO_REBUILD_URSELF(argc, argv) \
    do { \
        const char *source = __FILE__; \
        const char *binary = argv[0]; \
        if (needs_rebuild(binary, &source, 1)) { \
            rename(binary, concat(binary, ".old")); \
            CMD("cc", "-o", binary, source); \
            CMD(binary); \
            exit(0); \
        } \
    } while(0)

int needs_rebuild(const char *output, const char **inputs, size_t inputs_count);
void CMD(const char *cmd, ...);
const char *concat(const char *a, const char *b);

#ifdef NOBUILD_IMPLEMENTATION

int needs_rebuild(const char *output, const char **inputs, size_t inputs_count) {
    struct stat statbuf_output;
    if (stat(output, &statbuf_output) < 0) return 1;
    
    for (size_t i = 0; i < inputs_count; ++i) {
        struct stat statbuf_input;
        if (stat(inputs[i], &statbuf_input) < 0) return 1;
        if (statbuf_input.st_mtime > statbuf_output.st_mtime) return 1;
    }
    return 0;
}

void CMD(const char *cmd, ...) {
    char command[4096] = {0};
    strcat(command, cmd);
    
    va_list args;
    va_start(args, cmd);
    const char *arg;
    while ((arg = va_arg(args, const char*)) != NULL) {
        strcat(command, " ");
        strcat(command, arg);
    }
    va_end(args);
    
    printf("[CMD] %s\n", command);
    int ret = system(command);
    if (ret != 0) exit(1);
}

const char *concat(const char *a, const char *b) {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s%s", a, b);
    return buffer;
}

#endif // NOBUILD_IMPLEMENTATION
#endif // NOBUILD_H_
