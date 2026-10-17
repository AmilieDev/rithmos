// GPL-V2.0
// AmilieDev; 16/10/2026
// Main file for Rithmos. Starts the actual program, and hands off to init.

#include <stdio.h>
#include <string.h>

// Credits @ Mackron on GitHub for MiniAudio - a clean, and efficient sound API.
#include "miniaudio/miniaudio.h"

// src/init/init.h - Starts the actual MiniAudio engine.
#include "init/init.h"

int main(void){
	init();
	return 0;
}
