// GPL-V2.0
// AmilieDev; 16/10/2026
// Logging system for Rithmos, with appropriate colors. Logs to terminal, not any file.

#include <stdio.h>
#include <stdlib.h>

// Definining colours for use in the terminal. We'd like to make it fancy right?
#define ANSI_COLOUR_RED "\x1b[31m"
#define ANSI_COLOUR_GREEN "\x1b[32m"
#define ANSI_COLOUR_YELLOW "\x1b[33m"
#define ANSI_COLOUR_RESET "\x1b[0m"

void log_info(const char *message){
	printf("[Info] %s\n", message);
}

void log_error(const char *message){
	printf(ANSI_COLOUR_RED "[Error] %s\n" ANSI_COLOUR_RESET, message);
}

void log_warning(const char *message){
	printf(ANSI_COLOUR_YELLOW "[Warning] %s\n" ANSI_COLOUR_RESET, message);
}

void log_panic(const char *message){
	printf(ANSI_COLOUR_RED "[!!!PANIC!!!] Something went REALLY wrong...\n%s\n" ANSI_COLOUR_RESET, message);
	exit(EXIT_FAILURE);
}
