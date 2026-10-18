// GPL-V2.0
// AmilieDev; 16/10/2026
// Logging system for Rithmos, with appropriate colors. Logs to terminal, not any file.

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "logging.h"

// Definining colours for use in the terminal. We'd like to make it fancy right?
#define ANSI_COLOUR_RED "\x1b[31m"
#define ANSI_COLOUR_GREEN "\x1b[32m"
#define ANSI_COLOUR_YELLOW "\x1b[33m"
#define ANSI_COLOUR_RESET "\x1b[0m"

void logger(enum LOG_TYPE type, const char *message, ...){
	if(message == NULL){
		fprintf(stderr, "[error]: NULL logging message.");
		return;
	}
	// https://en.cppreference.com/c/io/vfprintf
	// Look here for documentation on how this works. Make logging more dynamic and lets us put as many types of info as we want.
	va_list arguments1;
	va_start(arguments1, message);
	va_list arguments2;
	va_copy(arguments2, arguments1);

	int length = vsnprintf(NULL, 0, message, arguments1);
	va_end(arguments1);
	
	if(length < 0){
		va_end(arguments2);
		fprintf(stderr, "[error]: Failed to format a logging message.\n");
		return;
	}

	char buf[(size_t)length + 1];

	int result = vsnprintf(buf, sizeof buf, message, arguments2);
	va_end(arguments2);

	if(result < 0 || result >= (int)sizeof buf){
		fprintf(stderr, "[error]: Failed to write formatted log message.");
		return;
	}

	if(type == INFO){
		printf("[info]: %s\n", buf);
	}else if(type == WARNING){
		printf(ANSI_COLOUR_YELLOW "[warning]: %s\n" ANSI_COLOUR_RESET, buf);
	}else if(type == ERROR){
		printf(ANSI_COLOUR_RED "[error]: %s\n" ANSI_COLOUR_RESET, buf);
	}else if(type == PANIC){
		printf(ANSI_COLOUR_RED "[panic]: %s\n" ANSI_COLOUR_RESET, buf);
		exit(1);
	}else{
		printf(ANSI_COLOUR_RED "[error]: Invalid logging type entered. Check your function.\n" ANSI_COLOUR_RESET);
	}
	
}