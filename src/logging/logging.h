// GPL-V2.0
// AmilieDev; 16/10/2026
// Header file for Rithmos logging system.

#ifndef LOGGING_H
#define LOGGING_H

enum LOG_TYPE {
	INFO,
	WARNING,
	ERROR,
	PANIC
};

void logger(enum LOG_TYPE type, const char *message, ...);

#endif
